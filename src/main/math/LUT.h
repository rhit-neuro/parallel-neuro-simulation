#if INCLUDE_LUT_SUPPORT
#ifndef PARALLEL_NEURON_SIMULATION_LUT_H
#define PARALLEL_NEURON_SIMULATION_LUT_H

#include <vector>
#include <string>

namespace lut {
   enum CurveSelect {

    // --- Curve 0: Sigmoid --- //
    // Note that we flip the a-sign at some point because the LUT values for the sigmoid
    // were generated backwards. Also note that the hardfloat version of the LUT is using
    // an FMADD and so it needs to do a*x + b rather than a*(x+b). So the b-values are different 
                  //   a     b
    Mk2_FINF = 0, // -83 , 0.02     //0
    Mp_FINF,      // -120, 0.039    //1
    Mna_FINF,     // -150, 0.029    //2
    Hna_FINF,     //  500, 0.030    //3
    Mcaf_FINF,    // -600, 0.0467   //4
    Hcaf_FINF,    //  350, 0.0555   //5
    Mcas_FINF,    // -420, 0.0472   //6
    Hcas_FINF,    //  360, 0.055    //7
    Mk1_FINF,     // -143, 0.021    //8
    Hk1_FINF,     //  111, 0.028    //9
    Mka_FINF,     // -130, 0.044    //10
    Hka_FINF,     //  160, 0.063    //11
    Mkf_FINF,     // -100, 0.022    //12

    // --- Curve 0: Sigmoid again --- //
    Mk2_TAU,      //  200, 0.035    //13
    Mp_TAU,       //  400, 0.057    //14
    Hna_TAU,      //  500, 0.028    //15
    Hcaf_TAU,     //  270, 0.055    //16
    Mcas_TAU,     // -400, 0.0487   //17
    Hcas_TAU,     // -250, 0.043    //18
    Mk1_TAU,      //  150, 0.016    //19
    Hk1_TAU,      // -143, 0.013    //20
    Mka_TAU,      //  200, 0.03     //21
    Hka_TAU,      // -300, 0.055    //22
    Mkf_TAU,      // -100, 0.022    //23
    Mh_TAU,       // -100, 0.073    //24

    // --- Curve 2: 1/cosh. Leela calls it INVCOS or ICOS depending on the day. --- //
    Hna_ICOS,     //  300, 0.027    //25
    Mkf_ICOS,     //  100, 0.04     //26
    Mcaf_ICOS,    // -330, 0.0467   //27

    // --- Curve 1: Demented sigmoid --- //
    FHINF,        //  180, 0.047    //28

    NUM_CURVES
  };

  class LUT {
    public:
      virtual double interpolate(double vMem, CurveSelect curveSelect) = 0;
  };

  class SoftLUT : public lut::LUT {
    public:
      SoftLUT(const std::string& fileName) {
        initialize(fileName);
      }
      double interpolate(double vMem, CurveSelect curveSelect);

    private:
      void initialize(const std::string& fileName);
      std::vector<float> vMemss[NUM_CURVES];
      std::vector<float> slopess[NUM_CURVES];
      std::vector<float> offsetss[NUM_CURVES];
  };

#if RISCV
  class HardLUTROM : public lut::LUT {
    public:
      double interpolate(double vMem, CurveSelect curveSelect);
      float getSlope(float vMem, CurveSelect curveSelect);
      float getScaledVmem(float vMem, CurveSelect curveSelect);
      float getOffset(float vMem, CurveSelect curveSelect);
  };
#endif //RISCV
}

extern lut::LUT *lutSingleton;

#endif //PARALLEL_NEURON_SIMULATION_LUT_H
#endif //INCLUDE_LUT_SUPPORT