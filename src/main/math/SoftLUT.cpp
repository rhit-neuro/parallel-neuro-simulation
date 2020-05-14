#if INCLUDE_LUT_SUPPORT

#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

#include "LUT.h"

// Expected file format (CSV):
// curve 1 vMem
// curve 1 offset
// curve 1 slope
// curve 2 vMem
// etc.

void lut::SoftLUT::initialize(const std::string& fileName) {
  // Load file with LUT constants
  std::ifstream lutFile(fileName);

  if (lutFile.is_open()) {
    std::string line;
    int lineNum = 0;

    // Read line by line
    while (std::getline(lutFile, line)) {
      std::istringstream iss(line);
      float num;
      char comma;
      // Every 3 lines is a new curve
      int curveSelect = lineNum / 3;

      // Num extracts a float from iss
      while (iss >> num) {
        // Decide whether num is a vMem, offset, or slope
        switch (lineNum % 3) {
          case 0:
            vMemss[curveSelect].push_back(num);
            break;
          case 1:
            offsetss[curveSelect].push_back(num);
            break;
          case 2:
            slopess[curveSelect].push_back(num);
            break;
        }


        // Consume a comma from iss before looping for next float
        iss >> comma;
      }

      lineNum++;
    }
  } else {
    throw std::runtime_error("could not open lutFile");
  }
}

double lut::SoftLUT::interpolate(double vMem, lut::CurveSelect curveSelect) {

 float a[] = {83.0000,
              120.0000,
              150.0000,
              -500.0000,
              600.0000,
              -350.0000,
              420.0000,
              -360.0000,
              143.0000,
              -111.0000,
              130.0000,
              -160.0000,
              100.0000,
              -200.0000,
              -400.0000,
              -500.0000,
              -270.0000,
              400.0000,
              250.0000,
              -150.0000,
              143.0000,
              -200.0000,
              300.0000,
              100.0000,
              100.0000,
              300.0000,
              100.0000,
              -330.0000,
              180.0000	};

 float b[] = {  1.6600,
                4.6800,
                4.3500,
                -15.0000,
                28.0200,
                -19.4250,
                19.8240,
                -19.8000,
                3.0030,
                -3.1080,
                5.7200,
                -10.0800,
                2.2000,
                -7.0000,
                -22.8000,
                -14.0000,
                -14.8500,
                19.4800,
                10.7500,
                -2.4000,
                1.8590,
                -6.0000,
                16.5000,
                2.2000,
                7.3000,
                8.1000,
                4.0000,
                -15.4110,
                8.4600	};

   float aSel = a[curveSelect];
   float bSel = b[curveSelect];

   int threeCurveSel;
   if (curveSelect == 28){
            threeCurveSel = 1;
   } else if (curveSelect > 24){
            threeCurveSel = 2;
   } else {
            threeCurveSel = 0;
   }

   vMem = aSel * vMem + bSel;

  std::vector<float> vMems = vMemss[threeCurveSel];
  std::vector<float> slopes = slopess[threeCurveSel];
  std::vector<float> offsets = offsetss[threeCurveSel];

  // Find where vMem indexes in LUT
  int leftBound = 0;
  int rightBound = vMems.size() - 1;
  int checkIndex;
  while (leftBound < rightBound) {
    checkIndex = (rightBound + leftBound) / 2 + 1;
    if (vMem < vMems[checkIndex]) {
      rightBound = checkIndex - 1;
    } else {
      leftBound = checkIndex;
    }
  }

  return slopes[leftBound] * vMem + offsets[leftBound];
}
#endif //INCLUDE_LUT_SUPPORT
