#ifndef PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
#define PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H


#include <vector>

namespace global_definitions {
  typedef std::vector<double> storage_type;

  typedef void observer_function(const storage_type &x, const double t);

  namespace sequential {
    typedef void ode_system_function(const storage_type &x, storage_type &dxdt, double t);
  }

  struct InitialCondition {
    int NUM_OF_NEURONS;
    double STATE_VARIABLES[];
  };
}


#endif //PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
