#ifndef PARALLEL_NEURON_SIMULATION_ODE_H
#define PARALLEL_NEURON_SIMULATION_ODE_H


#include "../global/GlobalDefinitions.h"

using namespace global_definitions;

namespace ode {
  namespace hodgkinhuxley {
    /**
     * Calculates the next set of derivatives based on the current state variables and the time differential.
     * This function must exist for all systems of ODEs to be solved by
     * @param x Values of current state variables
     * @param dxdt Placeholder for new values for the derivatives
     * @param dt Current time value, might be unused by the calculation
     */
    void calculateNextState(const storage_type &x, storage_type &dxdt, double t);

    namespace curve {
      double finf(double a, double b, double v);
      double fhinf(double v);
      double tau(double a, double b, double c, double d, double v);
      double tauhna(double v);
      double taumkf(double v);
      double taumcaf(double v);
    }

    namespace current {
      // TODO Investigate better design
      double ina(const storage_type &x, int neuron_num);
      double ip(const storage_type &x, int neuron_num);
      double icaf(const storage_type &x, int neuron_num);
      double icas(const storage_type &x, int neuron_num);
      double ik1(const storage_type &x, int neuron_num);
      double ik2(const storage_type &x, int neuron_num);
      double ika(const storage_type &x, int neuron_num);
      double ikf(const storage_type &x, int neuron_num);
      double ih(const storage_type &x, int neuron_num);
      double il(const storage_type &x, int neuron_num);
      double ica(const storage_type &x, int neuron_num, int synapse_num);
      double isyns(const storage_type &x, int synapse_num);
    }
  }
}


#endif //PARALLEL_NEURON_SIMULATION_ODE_H
