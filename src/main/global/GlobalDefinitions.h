#ifndef PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
#define PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H


#include <vector>
#include <boost/program_options.hpp>


namespace global_definitions {
  typedef std::vector<double> storage_type;

  typedef void observer_function(const storage_type &x, const double t);

  namespace sequential {
    typedef void ode_system_function(const storage_type &x, storage_type &dxdt, double t);
    
    // TODO: FIX 
    // typedef ???? ode_integrator;
  }

  namespace po = boost::program_options;
}


#endif //PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
