#include "Factory.h"
#include "../math/ODE.h"


sequential::ode_system_function * factory::equation::getEquation() {
  return &ode::hodgkinhuxley::calculateNextState;
}
