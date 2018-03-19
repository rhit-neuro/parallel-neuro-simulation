#if INCLUDE_LUT_SUPPORT
#include "ODE.h"

#include <lut_support-a7d4c9fa7d6a4c1a5c1494d29d99617b392c8255/lut_support.h>

using namespace config;

using namespace ode::hodgkinhuxley_lut;

void calculateNextState(const storage_type &xs, storage_type &dxdts, double t) {
  ProgramConfig c = ProgramConfig::getInstance();
  const int numOfNeurons = c.numOfNeurons;
  double *arrV = c.getVArray(const_cast<storage_type &>(xs));
  double *arrdVdt = c.getVArray(dxdts);
  #pragma omp parallel for default(shared)
  for (int i = 0; i < numOfNeurons; i++) {
    double currentV = arrV[i];
    double lutResult;
    findLUTValues(currentV, lutResult);
    arrdVdt[i] = lutResult;
  }
}
#endif
