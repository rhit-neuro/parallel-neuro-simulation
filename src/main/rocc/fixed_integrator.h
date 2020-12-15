// See LICENSE for license details.
#if RISCV

#include "../../include/rocc-software/src/xcustom.h"

#define FUNCT_WHOLE_STEP 5
#define FUNCT_HALF_STEP 6

#define XCUSTOM_ACC 0

#define integrateWholeStep(rocc_rd, rocc_rs1, rocc_rs2) \
	ROCC_INSTRUCTION(0, rocc_rd, rocc_rs1, rocc_rs2, FUNCT_WHOLE_STEP)
	
#define integrateHalfStep(rocc_rd, rocc_rs1, rocc_rs2) \
	ROCC_INSTRUCTION(0, rocc_rd, rocc_rs1, rocc_rs2, FUNCT_HALF_STEP)

#endif //RISCV
