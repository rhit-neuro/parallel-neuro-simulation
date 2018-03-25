#ifndef PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
#define PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H


#include <vector>
#include <boost/program_options.hpp>

namespace global_definitions {
  typedef std::vector<double> storage_type;

  typedef void observer_function(const storage_type &x, const double t);

  namespace sequential {
    typedef void ode_system_function(const storage_type &x, storage_type &dxdt, double t);
  }

  namespace generic_double_math_signatures {
    typedef double one_arg_double_math(double);
    typedef double two_args_double_math(double, double);
    typedef double three_args_double_math(double, double, double);
    typedef double four_args_double_math(double, double, double, double);
    typedef double five_args_double_math(double, double, double, double, double);
  }

  namespace po = boost::program_options;
}


#endif //PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
