#ifndef PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
#define PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H


namespace global_definitions {
  typedef void observer_function(const double &x, const double t);

  namespace sequential {
    typedef void ode_system_function(const double &x, double &dxdt, double t);
  }

  struct InitialCondition {
    int NUM_OF_NEURONS;
    double STATE_VARIABLES[];
  };
}


#endif //PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
