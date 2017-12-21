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
  }
}


#endif //PARALLEL_NEURON_SIMULATION_ODE_H
