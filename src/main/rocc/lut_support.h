// See LICENSE for license details.

#ifndef LUT_SUPPORT_H
#define LUT_SUPPORT_H

#include "../../include/rocc-software/src/xcustom.h"

#define FUNCT_LOOKUPOFFSET 0
#define FUNCT_LOOKUPSLOPE 1

#define XCUSTOM_ACC 0

#define lookupOffset(rocc_rd, rocc_rs1, rocc_rs2) \
  ROCC_INSTRUCTION(0, rocc_rd, rocc_rs1, rocc_rs2, FUNCT_LOOKUPOFFSET)

#define lookupSlope(rocc_rd, rocc_rs1, rocc_rs2) \
  ROCC_INSTRUCTION(0, rocc_rd, rocc_rs1, rocc_rs2, FUNCT_LOOKUPSLOPE)

#endif  // LUT_SUPPORT_H
