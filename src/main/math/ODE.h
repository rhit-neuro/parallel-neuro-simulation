#ifndef PARALLEL_NEURON_SIMULATION_ODE_H
#define PARALLEL_NEURON_SIMULATION_ODE_H


#include "../global/GlobalDefinitions.h"
#include "../state/ConfigAdapter.h"

using namespace global_definitions;
using namespace state;

namespace ode {
  namespace hodgkinhuxley {
    /**
     * Calculates the next set of derivatives based on the current state variables and the time differential.
     * This function must exist for all systems of ODEs to be solved by
     * @param xs Values of current state variables
     * @param dxdts Placeholder for new values for the derivatives
     * @param dt Current time value, might be unused by the calculation
     */
    void calculateNextState(const storage_type &xs, storage_type &dxdts, double t);

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
      double ina(double gbarna, double mna, double hna, double V, double Ena);
      double ip(double gbarp, double mp, double V, double Ena);
      double icaf(double gbarcaf, double mcaf, double hcaf, double V, double Eca);
      double icas(double gbarcas, double mcas, double hcas, double V, double Eca);
      double ik1(double gbark1, double mk1, double hk1, double V, double Ek);
      double ik2(double gbark2, double mk2, double hk2, double V, double Ek);
      double ika(double gbarka, double mka, double hka, double V, double Ek);
      double ikf(double gbarkf, double mkf, double V, double Ek);
      double ih(double gbarh, double mh, double V, double Eh);
      double il(double gbarl, double V, double El);
      double ica(double icaf, double icas, double A);
      double isyn(double cGraded, double Esyn, double V, double P, double M, double g,
                        SynapseConstants *allSynapses, ProtobufRepeatedInt32 &ownSynapses,
                        int numOfOwnSynapses);
      // Unimplemented
//      double isyng(double gbarsyng, double P, double C, double V, double Esyn);
//      double isyns(double x, NeuronConstants &n, SynapseConstants &s, int synapseIndex);
    }
  }
}


#endif //PARALLEL_NEURON_SIMULATION_ODE_H
