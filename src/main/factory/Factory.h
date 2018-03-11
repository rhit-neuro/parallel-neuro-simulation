#ifndef PARALLEL_NEURON_SIMULATION_FACTORY_H
#define PARALLEL_NEURON_SIMULATION_FACTORY_H

#include <proto/protobuf_config.pb.h>
#include <omp.h>
#include "../global/GlobalDefinitions.h"
#include "../math/ODE.h"

using namespace global_definitions;
using namespace protobuf_config;

namespace factory {
  namespace equation {
    sequential::ode_system_function * getEquation(po::variables_map &vm);
  }
}


#endif //PARALLEL_NEURON_SIMULATION_FACTORY_H
