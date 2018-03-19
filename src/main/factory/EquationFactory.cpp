#include "Factory.h"


sequential::ode_system_function * factory::equation::getEquation(po::variables_map &vm) {
#if USE_OPENMP
  const unsigned int num_threads_by_user = vm["num-threads"].as<unsigned int>();
  if (num_threads_by_user) { // Therefore if user specifies 0, this will be false
    omp_set_num_threads(num_threads_by_user);
  }
#endif
#if INCLUDE_LUT_SUPPORT
  const bool use_lut = vm["use-lut"].as<bool>();
  if (use_lut) {
    return &ode::hodgkinhuxley_lut::calculateNextState;
  }
#endif
  return &ode::hodgkinhuxley::calculateNextState;
}
