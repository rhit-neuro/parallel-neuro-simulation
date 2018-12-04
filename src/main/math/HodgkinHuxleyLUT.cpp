#if INCLUDE_LUT_SUPPORT
#include "ODE.h"


using namespace config;

void ode::hodgkinhuxley_lut::calculateNextState(const storage_type &xs, storage_type &dxdts, double t) {
  static ode::hodgkinhuxley_lut::HodgkinHuxleyLUTEquation equationInstance;
  equationInstance.calculateNextState(xs, dxdts, t);
}
#endif
