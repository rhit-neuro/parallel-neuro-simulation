#include "ODE.h"

using namespace state;

using namespace ode::hodgkinhuxley::curve;
using namespace ode::hodgkinhuxley::current;

void ode::hodgkinhuxley::calculateNextState(const storage_type &x, storage_type &dxdt, double t) {
  ConfigAdapter c = ConfigAdapter::getInstance();
  double* arrV = c.getVArray(const_cast<storage_type &>(x));
  double* arrMk2 = c.getMk2Array(const_cast<storage_type &>(x));
  double* arrMp = c.getMpArray(const_cast<storage_type &>(x));
  double* arrMna = c.getMnaArray(const_cast<storage_type &>(x));
  double* arrHna = c.getHnaArray(const_cast<storage_type &>(x));
  double* arrMcaf = c.getMcafArray(const_cast<storage_type &>(x));
  double* arrHcaf = c.getHcafArray(const_cast<storage_type &>(x));
  double* arrMcas = c.getMcasArray(const_cast<storage_type &>(x));
  double* arrHcas = c.getHcasArray(const_cast<storage_type &>(x));
  double* arrMk1 = c.getMk1Array(const_cast<storage_type &>(x));
  double* arrHk1 = c.getHk1Array(const_cast<storage_type &>(x));
  double* arrMka = c.getMkaArray(const_cast<storage_type &>(x));
  double* arrHka = c.getHkaArray(const_cast<storage_type &>(x));
  double* arrMkf = c.getMkfArray(const_cast<storage_type &>(x));
  double* arrMh = c.getMhArray(const_cast<storage_type &>(x));
  double* arrA = c.getAArray(const_cast<storage_type &>(x));
  double* arrP = c.getPArray(const_cast<storage_type &>(x));
  double* arrM = c.getMArray(const_cast<storage_type &>(x));
  double* arrG = c.getGArray(const_cast<storage_type &>(x));
  double* arrH = c.getHArray(const_cast<storage_type &>(x));

  double* arrdVdt = c.getVArray(dxdt);
  double* arrdMk2dt = c.getMk2Array(dxdt);
  double* arrdMpdt = c.getMpArray(dxdt);
  double* arrdMnadt = c.getMnaArray(dxdt);
  double* arrdHnadt = c.getHnaArray(dxdt);
  double* arrdMcafdt = c.getMcafArray(dxdt);
  double* arrdHcafdt = c.getHcafArray(dxdt);
  double* arrdMcasdt = c.getMcasArray(dxdt);
  double* arrdHcasdt = c.getHcasArray(dxdt);
  double* arrdMk1dt = c.getMk1Array(dxdt);
  double* arrdHk1dt = c.getHk1Array(dxdt);
  double* arrdMkadt = c.getMkaArray(dxdt);
  double* arrdHkadt = c.getHkaArray(dxdt);
  double* arrdMkfdt = c.getMkfArray(dxdt);
  double* arrdMhdt = c.getMhArray(dxdt);
  double* arrdAdt = c.getAArray(dxdt);
  double* arrdPdt = c.getPArray(dxdt);
  double* arrdMdt = c.getMArray(dxdt);
  double* arrdGdt = c.getGArray(dxdt);
  double* arrdHdt = c.getHArray(dxdt);

  const int numOfNeurons = c.numOfNeurons;
  const int numOfSynapses = c.numOfSynapses;


  for (int i = 0; i < numOfNeurons; i++) {
    const NeuronConstants &n = c.getNeuronConstantAt(i);
    const double V = arrV[i];
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        // Calculate dVdt
        arrdVdt[i] = -(ina(n.gbarna, arrMna[i], arrHna[i], V, n.ena) +
                       ip(n.gbarp, arrMp[i], V, n.ena) +
                       icaf(n.gbarcaf, arrMcaf[i], arrHcaf[i], V, n.eca) +
                       icas(n.gbarcas, arrMcas[i], arrHcas[i], V, n.eca) +
                       ik1(n.gbark1, arrMk1[i], arrHk1[i], V, n.ek) +
                       ik2(n.gbark2, arrMk2[i], V, n.ek) +
                       ika(n.gbarka, arrMka[i], arrHka[i], V, n.ek) +
                       ikf(n.gbarkf, arrMkf[i], V, n.ek) +
                       ih(n.gbarh, arrMh[i], V, n.eh) +
                       il(n.gbarl, V, n.el) +
                       isyn(V, arrP[i], arrM[i], arrG[i], c.getAllSynapseConstants(), *(n.incoming), n.incoming->size())
                      ) / n.capacitance;
      }
      #pragma omp section
      {
        // Calculate dMk2dt
        arrdMk2dt[i] = (finf(-83.0, 0.02, V) - arrMk2[i]) / tau(200.0, 0.035, 0.057, 0.043, V);
//      }
//      #pragma omp section
//      {
        // Calculate dMpdt
        arrdMpdt[i] = (finf(-120.0, 0.039, V) - arrMp[i]) / tau(400.0, 0.057, 0.01, 0.2, V);
//      }
//      #pragma omp section
//      {
        // Calculate dMnadt
        arrdMnadt[i] = (finf(-150.0, 0.029, V) - arrMna[i]) / 0.0001;
//      }
//      #pragma omp section
//      {
        // Calculate dHnadt
        arrdHnadt[i] = (finf(500.0, 0.030, V) - arrHna[i]) / tauhna(V);
//      }
//      #pragma omp section
//      {
        // Calculate dMcafdt
        arrdMcafdt[i] = (finf(-600.0, 0.0467, V) - arrMcaf[i]) / taumcaf(V);
//      }
//      #pragma omp section
//      {
        // Calculate dHcafdt
        arrdHcafdt[i] = (finf(350.0, 0.0555, V) - arrHcaf[i]) / tau(270.0, 0.055, 0.06, 0.31, V);
//      }
//      #pragma omp section
//      {
        // Calculate dMcasdt
        arrdMcasdt[i] = (finf(-420.0, 0.0472, V) - arrMcas[i]) / tau(-400.0, 0.0487, 0.005, 0.134, V);
//      }
//      #pragma omp section
//      {
        // Calculate dHcasdt
        arrdHcasdt[i] = (finf(360.0, 0.055, V) - arrHcas[i]) / tau(-250.0, 0.043, 0.2, 5.25, V);
//      }
//      #pragma omp section
//      {
        // Calculate dMk1dt
        arrdMk1dt[i] = (finf(-143.0, 0.021, V) - arrMk1[i]) / tau(150.0, 0.016, 0.001, 0.011, V);
//      }
//      #pragma omp section
//      {
        // Calculate dHk1dt
        arrdHk1dt[i] = (finf(111.0, 0.028, V) - arrHk1[i]) / tau(-143.0, 0.013, 0.5, 0.2, V);
//      }
//      #pragma omp section
//      {
        // Calculate dMkadt
        arrdMkadt[i] = (finf(-130.0, 0.044, V) - arrMka[i]) / tau(200.0, 0.03, 0.005, 0.011, V);
//      }
//      #pragma omp section
//      {
        // Calculate dHkadt
        arrdHkadt[i] = (finf(160.0, 0.063, V) - arrHka[i]) / tau(-300.0, 0.055, 0.026, 0.0085, V);
//      }
//      #pragma omp section
//      {
        // Calculate dMkfdt
        arrdMkfdt[i] = (finf(-100.0, 0.022, V) - arrMkf[i]) / taumkf(V);
//      }
//      #pragma omp section
//      {
        // Calculate dMhdt
        arrdMhdt[i] = (fhinf(V) - arrMh[i]) / tau(-100.0, 0.073, 0.7, 1.7, V);
      }
    };
  }

  #pragma omp parallel for
  for (int j = 0; j < numOfSynapses; j++) {
    const SynapseConstants &s = c.getSynapseConstantAt(j);
    const int sourceNeuronIndex = s.source;
    const NeuronConstants &n = c.getNeuronConstantAt(sourceNeuronIndex);
    const double V = arrV[sourceNeuronIndex];
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        // Calculate dAdt
        arrdAdt[j] = (1.0e-10 / (1 + exp(-100.0 * (V + 0.02))) - arrA[j]) / 0.2;
      }
      #pragma omp section
      {
        // Calculate dPdt
        // TODO Cache the result from loop above to save time
        arrdPdt[j] = ica(
          icaf(n.gbarcaf, arrMcaf[sourceNeuronIndex], arrHcaf[sourceNeuronIndex], V, n.eca),
          icas(n.gbarcas, arrMcas[sourceNeuronIndex], arrHcas[sourceNeuronIndex], V, n.eca),
          arrA[j]
        ) - s.buffering * arrP[j];
      }
      #pragma omp section
      {
        // Calculate dMdt
        arrdMdt[j] = (0.1 + 0.9 / (1 + exp(-1000.0 * (V + 0.04))) - arrM[j]) / 0.2;
//      }
//      #pragma omp section
//      {
        // Calculate dGdt
        arrdGdt[j] = -arrG[j] / s.tauDecay + arrH[j];
//      }
//      #pragma omp section
//      {
        // Calculate dHdt
        arrdHdt[j] = -arrH[j] / s.tauRise +
                           (V > s.thresholdV ? s.h0 : 0);
      }
    };
  }
}
