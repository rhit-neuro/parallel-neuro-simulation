#ifndef PARALLEL_NEURON_SIMULATION_FACTORY_H
#define PARALLEL_NEURON_SIMULATION_FACTORY_H

#include <proto/protobuf_config.pb.h>
#include "../global/GlobalDefinitions.h"

using namespace global_definitions;
using namespace protobuf_config;

namespace factory {
  namespace equation {
    sequential::ode_system_function * getEquation();
  }
}


#endif //PARALLEL_NEURON_SIMULATION_FACTORY_H
