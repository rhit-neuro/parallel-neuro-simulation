#include "Factory.h"

using namespace input_config;

InitialCondition& factory::initialcondition::getInitialCondition(Config config) {
  InitialCondition ic;
  return ic;
}
