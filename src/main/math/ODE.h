#ifndef PARALLEL_NEURON_SIMULATION_ODE_H
#define PARALLEL_NEURON_SIMULATION_ODE_H


#include "../global/GlobalDefinitions.h"
#include "../config/ProgramConfig.h"

using namespace global_definitions;
using namespace config;

namespace ode {
  namespace hodgkinhuxley {
    void calculateNextState(const storage_type &xs, storage_type &dxdts, double t);

    namespace curve {
      double finf(double a, double b, double v);
      double fhinf(double v);
      double tau(double a, double b, double c, double d, double v);
      double tauhna(double v);
      double taumkf(double v);
      double taumcaf(double v);

      double dMk2dt(double V, double mk2);
      double dMpdt(double V, double mp);
      double dMnadt(double V, double mna);
      double dHnadt(double V, double hna);
      double dMcafdt(double V, double mcaf);
      double dHcafdt(double V, double hcaf);
      double dMcasdt(double V, double mcas);
      double dHcasdt(double V, double hcas);
      double dMk1dt(double V, double mk1);
      double dHk1dt(double V, double hk1);
      double dMkadt(double V, double mka);
      double dHkadt(double V, double hka);
      double dMkfdt(double V, double mkf);
      double dMhdt(double V, double mh);
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

    extern unsigned long long numSteps;

    class HodgkinHuxleyEquation {
      public:
        HodgkinHuxleyEquation();
        /**
         * Calculates the next set of derivatives based on the current state variables and the time differential.
         * This function must exist for all systems of ODEs to be solved by
         * @param xs Values of current state variables
         * @param dxdts Placeholder for new values for the derivatives
         * @param dt Current time value, might be unused by the calculation
         */
        void calculateNextState(const storage_type &xs, storage_type &dxdts, double t);

      protected:
        // We use function pointers to allow easy composition
        double (* dMk2dt) (double V, double mk2) = ::ode::hodgkinhuxley::curve::dMk2dt;
        double (* dMpdt) (double V, double mp) = ::ode::hodgkinhuxley::curve::dMpdt;
        double (* dMnadt) (double V, double mna) = ::ode::hodgkinhuxley::curve::dMnadt;
        double (* dHnadt) (double V, double hna) = ::ode::hodgkinhuxley::curve::dHnadt;
        double (* dMcafdt) (double V, double mcaf) = ::ode::hodgkinhuxley::curve::dMcafdt;
        double (* dHcafdt) (double V, double hcaf) = ::ode::hodgkinhuxley::curve::dHcafdt;
        double (* dMcasdt) (double V, double mcas) = ::ode::hodgkinhuxley::curve::dMcasdt;
        double (* dHcasdt) (double V, double hcas) = ::ode::hodgkinhuxley::curve::dHcasdt;
        double (* dMk1dt) (double V, double mk1) = ::ode::hodgkinhuxley::curve::dMk1dt;
        double (* dHk1dt) (double V, double hk1) = ::ode::hodgkinhuxley::curve::dHk1dt;
        double (* dMkadt) (double V, double mka) = ::ode::hodgkinhuxley::curve::dMkadt;
        double (* dHkadt) (double V, double hka) = ::ode::hodgkinhuxley::curve::dHkadt;
        double (* dMkfdt) (double V, double mkf) = ::ode::hodgkinhuxley::curve::dMkfdt;
        double (* dMhdt) (double V, double mh) = ::ode::hodgkinhuxley::curve::dMhdt;

        double (* ina) (double gbarna, double mna, double hna, double V, double Ena) = ::ode::hodgkinhuxley::current::ina;
        double (* ip) (double gbarp, double mp, double V, double Ena) = ::ode::hodgkinhuxley::current::ip;
        double (* icaf) (double gbarcaf, double mcaf, double hcaf, double V, double Eca) = ::ode::hodgkinhuxley::current::icaf;
        double (* icas) (double gbarcas, double mcas, double hcas, double V, double Eca) = ::ode::hodgkinhuxley::current::icas;
        double (* ik1) (double gbark1, double mk1, double hk1, double V, double Ek) = ::ode::hodgkinhuxley::current::ik1;
        double (* ik2) (double gbark2, double mk2, double V, double Ek) = ::ode::hodgkinhuxley::current::ik2;
        double (* ika) (double gbarka, double mka, double hka, double V, double Ek) = ::ode::hodgkinhuxley::current::ika;
        double (* ikf) (double gbarkf, double mkf, double V, double Ek) = ::ode::hodgkinhuxley::current::ikf;
        double (* ih) (double gbarh, double mh, double V, double Eh) = ::ode::hodgkinhuxley::current::ih;
        double (* il) (double gbarl, double V, double El) = ::ode::hodgkinhuxley::current::il;
        double (* ica) (double icaf, double icas, double A) = ::ode::hodgkinhuxley::current::ica;
        double (* isyns) (double V, double *arrP, double *arrM, double *arrG, SynapseConstants *allSynapses,
                          ProtobufRepeatedInt32 &ownSynapses, int numOfOwnSynapses) = ::ode::hodgkinhuxley::current::isyns;

        // Expose config to subclasses
        ProgramConfig *pc;
    };
  }
#if INCLUDE_LUT_SUPPORT
  namespace hodgkinhuxley_lut {
    namespace curve {
      double dMk2dt(double V, double mk2);
      double dMpdt(double V, double mp);
      double dMnadt(double V, double mna);
      double dHnadt(double V, double hna);
      double dMcafdt(double V, double mcaf);
      double dHcafdt(double V, double hcaf);
      double dMcasdt(double V, double mcas);
      double dHcasdt(double V, double hcas);
      double dMk1dt(double V, double mk1);
      double dHk1dt(double V, double hk1);
      double dMkadt(double V, double mka);
      double dHkadt(double V, double hka);
      double dMkfdt(double V, double mkf);
      double dMhdt(double V, double mh);
    }

    class HodgkinHuxleyLUTEquation : public ::ode::hodgkinhuxley::HodgkinHuxleyEquation {
      public:
        HodgkinHuxleyLUTEquation() {
          dMk2dt = ::ode::hodgkinhuxley_lut::curve::dMk2dt;
          dMpdt = ::ode::hodgkinhuxley_lut::curve::dMpdt;
          dMnadt = ::ode::hodgkinhuxley_lut::curve::dMnadt;
          dHnadt = ::ode::hodgkinhuxley_lut::curve::dHnadt;
          dMcafdt = ::ode::hodgkinhuxley_lut::curve::dMcafdt;
          dHcafdt = ::ode::hodgkinhuxley_lut::curve::dHcafdt;
          dMcasdt = ::ode::hodgkinhuxley_lut::curve::dMcasdt;
          dHcasdt = ::ode::hodgkinhuxley_lut::curve::dHcasdt;
          dMk1dt = ::ode::hodgkinhuxley_lut::curve::dMk1dt;
          dHk1dt = ::ode::hodgkinhuxley_lut::curve::dHk1dt;
          dMkadt = ::ode::hodgkinhuxley_lut::curve::dMkadt;
          dHkadt = ::ode::hodgkinhuxley_lut::curve::dHkadt;
          dMkfdt = ::ode::hodgkinhuxley_lut::curve::dMkfdt;
          dMhdt = ::ode::hodgkinhuxley_lut::curve::dMhdt;
        }
    };

    void calculateNextState(const storage_type &xs, storage_type &dxdts, double t);
  }
#endif
}


#endif //PARALLEL_NEURON_SIMULATION_ODE_H
