// See LICENSE for license details.

#ifndef LUT_SUPPORT_H
#define LUT_SUPPORT_H

#include "../../include/rocc-software/src/xcustom.h"

#define FUNCT_LOOKUPSLOPE 0 //opcode 0b0001011
#define FUNCT_LOOKUPOFFSET 1 //opcode 0b0101011

#define XCUSTOM_ACC 0

#define lookupSlope(rocc_rd, rocc_rs1, rocc_rs2) \
  ROCC_INSTRUCTION(0, rocc_rd, rocc_rs1, rocc_rs2, FUNCT_LOOKUPSLOPE)

#define lookupOffset(rocc_rd, rocc_rs1, rocc_rs2) \
  ROCC_INSTRUCTION(0, rocc_rd, rocc_rs1, rocc_rs2, FUNCT_LOOKUPOFFSET)

#endif  // LUT_SUPPORT_H
