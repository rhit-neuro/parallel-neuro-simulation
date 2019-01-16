#if INCLUDE_LUT_SUPPORT
#if RISCV


#include "../rocc/lut_support.h"
#include "LUT.h"

double lut::HardLUTROM::interpolate(double vMem, lut::CurveSelect curveSelect) {
    float m, b;
    // Lookup slope
    lookupSlope(m, vMem, curveSelect);
    // Lookup offset
    lookupOffset(b, vMem, curveSelect);

    return vMem * m + b;
}

#endif //RISCV
#endif //INCLUDE_LUT_SUPPORT