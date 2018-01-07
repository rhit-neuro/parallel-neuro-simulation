#ifndef PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
#define PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H


namespace global_definitions {
  typedef void observer_function(const double &x, const double t);

  namespace sequential {
    typedef void ode_system_function(const double &x, double &dxdt, double t);
  }

  namespace offsets {
    // Offsets for neurons
    const short OFF_V = 0;
    const short OFF_mk2 = 1;
    const short OFF_mp = 2;
    const short OFF_mna = 3;
    const short OFF_hna = 4;
    const short OFF_mcaf = 5;
    const short OFF_hcaf = 6;
    const short OFF_mcas = 7;
    const short OFF_hcas = 8;
    const short OFF_mk1 = 9;
    const short OFF_hk1 = 10;
    const short OFF_mka = 11;
    const short OFF_hka = 12;
    const short OFF_mkf = 13;
    const short OFF_mh = 14;

    const short NUM_OF_NEURON_VARIABLES = 15;

    // Offsets for synapses
    const short OFF_A = 0;
    const short OFF_P = 1;
    const short OFF_M = 2;
    const short OFF_g = 3;
    const short OFF_h = 4;

    const short NUM_OF_SYNAPSE_VARIABLES = 5;
  }

  struct InitialCondition {
    int NUM_OF_NEURONS;
    double STATE_VARIABLES[];
  };
}


#endif //PARALLEL_NEURON_SIMULATION_GLOBALDEFINITIONS_H
