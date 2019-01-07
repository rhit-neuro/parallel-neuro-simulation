#if INCLUDE_LUT_SUPPORT


#include "LUT.h"

void lut::SoftLUT::initialize() {
    // Read in csv with lut values
}

double lut::SoftLUT::interpolate(double vMem, lut::CurveSelect curveSelect) {
    // Lookup right value in local arrays
    callcount++;
    return 0.5;
}
#endif //INCLUDE_LUT_SUPPORT