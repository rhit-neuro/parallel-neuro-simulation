#ifndef PARALLEL_NEURON_SIMULATION_FACTORY_H
#define PARALLEL_NEURON_SIMULATION_FACTORY_H

#include <proto/input_config.pb.h>
#include "../global/GlobalDefinitions.h"

using namespace global_definitions;
using namespace input_config;

namespace factory {
  namespace equation {
    sequential::ode_system_function * getEquation();
  }

  namespace initialcondition {
    InitialCondition& getInitialCondition(Config config);
  }
}


#endif //PARALLEL_NEURON_SIMULATION_FACTORY_H
