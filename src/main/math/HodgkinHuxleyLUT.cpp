#if INCLUDE_LUT_SUPPORT
#include "ODE.h"


using namespace config;

using namespace ode::hodgkinhuxley_lut;

void calculateNextState(const storage_type &xs, storage_type &dxdts, double t) {
  static HodgkinHuxleyLUTEquation equationInstance;
  equationInstance.calculateNextState(xs, dxdts, t);
}
#endif
