#ifndef PARALLEL_NEURON_SIMULATION_ODE_H
#define PARALLEL_NEURON_SIMULATION_ODE_H


namespace ode {
  namespace hodgkinhuxley {
    /**
     * Calculates the next set of derivatives based on the current state variables and the time differential.
     * This function must exist for all systems of ODEs to be solved by
     * @param x Values of current state variables
     * @param dxdt Placeholder for new values for the derivatives
     * @param dt Current time value, might be unused by the calculation
     */
    void calculateNextState(const double &x, double &dxdt, double t);

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
      double ina(const double &x, int neuron_num);
      double ip(const double &x, int neuron_num);
      double icaf(const double &x, int neuron_num);
      double icas(const double &x, int neuron_num);
      double ik1(const double &x, int neuron_num);
      double ik2(const double &x, int neuron_num);
      double ika(const double &x, int neuron_num);
      double ikf(const double &x, int neuron_num);
      double ih(const double &x, int neuron_num);
      double il(const double &x, int neuron_num);
      double ica(const double &x, int neuron_num, int synapse_num);
      double isyns(const double &x, int synapse_num);
    }
  }
}


#endif //PARALLEL_NEURON_SIMULATION_ODE_H
