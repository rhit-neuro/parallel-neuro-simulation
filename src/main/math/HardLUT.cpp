#if INCLUDE_LUT_SUPPORT
#if RISCV


#include "../rocc/lut_support.h"
#include "LUT.h"

double lut::HardLUTROM::interpolate(double vMem, lut::CurveSelect curveSelect) {
    return getSlope(vMem, curveSelect) * vMem + getOffset(vMem, curveSelect);
}

float lut::HardLUTROM::getSlope(float vMem, lut::CurveSelect curveSelect) {
    uint slope;
    lookupSlope(slope, *(uint *)&vMem, curveSelect);
    return *(float *)&slope;
}

float lut::HardLUTROM::getOffset(float vMem, lut::CurveSelect curveSelect) {
    uint offset;
    lookupOffset(offset, *(uint *)&vMem, curveSelect);
    return *(float *)&offset;
}

#endif //RISCV
#endif //INCLUDE_LUT_SUPPORT