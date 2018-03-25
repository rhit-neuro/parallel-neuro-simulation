#ifndef PARALLEL_NEURON_SIMULATION_ODE_H
#define PARALLEL_NEURON_SIMULATION_ODE_H


#include "../global/GlobalDefinitions.h"
#include "../config/ProgramConfig.h"

using namespace global_definitions;
using namespace config;

namespace ode {
  namespace hodgkinhuxley {
    using namespace generic_double_math_signatures;
    using namespace ode::hodgkinhuxley;

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
      double ik2(double gbark2, double mk2, double V, double Ek);
      double ika(double gbarka, double mka, double hka, double V, double Ek);
      double ikf(double gbarkf, double mkf, double V, double Ek);
      double ih(double gbarh, double mh, double V, double Eh);
      double il(double gbarl, double V, double El);
      double ica(double icaf, double icas, double A);
      double isyns(double V, double *arrP, double *arrM, double *arrG, SynapseConstants *allSynapses,
                   ProtobufRepeatedInt32 &ownSynapses, int numOfOwnSynapses);
      // Unimplemented
//      double isyng(double gbarsyng, double P, double C, double V, double Esyn);
//      double isyns(double x, NeuronConstants &n, SynapseConstants &s, int synapseIndex);
    }

    class HodgkinHuxleyEquation {
      public:
        explicit HodgkinHuxleyEquation();
        /**
         * Calculates the next set of derivatives based on the current state variables and the time differential.
         * This function must exist for all systems of ODEs to be solved by
         * @param xs Values of current state variables
         * @param dxdts Placeholder for new values for the derivatives
         * @param dt Current time value, might be unused by the calculation
         */
        void calculateNextState(const storage_type &xs, storage_type &dxdts, double t);

        three_args_double_math * finf = curve::finf;
        one_arg_double_math * fhinf = curve::fhinf;
        five_args_double_math * tau = curve::tau;
        one_arg_double_math * tauhna = curve::tauhna;
        one_arg_double_math * taumkf = curve::taumkf;
        one_arg_double_math * taumcaf = curve::taumcaf;

        five_args_double_math * ina = current::ina;
        four_args_double_math * ip = current::ip;
        five_args_double_math * icaf = current::icaf;
        five_args_double_math * icas = current::icas;
        five_args_double_math * ik1 = current::ik1;
        four_args_double_math * ik2 = current::ik2;
        five_args_double_math * ika = current::ika;
        four_args_double_math * ikf = current::ikf;
        four_args_double_math * ih = current::ih;
        three_args_double_math * il = current::il;
        three_args_double_math * ica = current::ica;
        double (* isyns) (double, double *, double *, double *, SynapseConstants *,
                                                      ProtobufRepeatedInt32 &, int) = current::isyns;
      private:
        ProgramConfig *pc;
    };
  }
#if INCLUDE_LUT_SUPPORT
  namespace hodgkinhuxley_lut {
    void calculateNextState(const storage_type &xs, storage_type &dxdts, double t);
  }
#endif
}


#endif //PARALLEL_NEURON_SIMULATION_ODE_H
