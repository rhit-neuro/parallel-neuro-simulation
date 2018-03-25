#include "ODE.h"

using namespace config;

void ode::hodgkinhuxley::calculateNextState(const storage_type &xs, storage_type &dxdts, double t)  {
  static HodgkinHuxleyEquation equationInstance;
  return equationInstance.calculateNextState(xs, dxdts, t);
}

ode::hodgkinhuxley::HodgkinHuxleyEquation::HodgkinHuxleyEquation() {
  this->pc = &(ProgramConfig::getInstance());
}

void ode::hodgkinhuxley::HodgkinHuxleyEquation::calculateNextState(const storage_type &x, storage_type &dxdt, double t) {
  ProgramConfig &c = *pc;
  double *arrV = c.getVArray(const_cast<storage_type &>(x));
  double *arrMk2 = c.getMk2Array(const_cast<storage_type &>(x));
  double *arrMp = c.getMpArray(const_cast<storage_type &>(x));
  double *arrMna = c.getMnaArray(const_cast<storage_type &>(x));
  double *arrHna = c.getHnaArray(const_cast<storage_type &>(x));
  double *arrMcaf = c.getMcafArray(const_cast<storage_type &>(x));
  double *arrHcaf = c.getHcafArray(const_cast<storage_type &>(x));
  double *arrMcas = c.getMcasArray(const_cast<storage_type &>(x));
  double *arrHcas = c.getHcasArray(const_cast<storage_type &>(x));
  double *arrMk1 = c.getMk1Array(const_cast<storage_type &>(x));
  double *arrHk1 = c.getHk1Array(const_cast<storage_type &>(x));
  double *arrMka = c.getMkaArray(const_cast<storage_type &>(x));
  double *arrHka = c.getHkaArray(const_cast<storage_type &>(x));
  double *arrMkf = c.getMkfArray(const_cast<storage_type &>(x));
  double *arrMh = c.getMhArray(const_cast<storage_type &>(x));
  double *arrA = c.getAArray(const_cast<storage_type &>(x));
  double *arrP = c.getPArray(const_cast<storage_type &>(x));
  double *arrM = c.getMArray(const_cast<storage_type &>(x));
  double *arrG = c.getGArray(const_cast<storage_type &>(x));
  double *arrH = c.getHArray(const_cast<storage_type &>(x));

  double *arrdVdt = c.getVArray(dxdt);
  double *arrdMk2dt = c.getMk2Array(dxdt);
  double *arrdMpdt = c.getMpArray(dxdt);
  double *arrdMnadt = c.getMnaArray(dxdt);
  double *arrdHnadt = c.getHnaArray(dxdt);
  double *arrdMcafdt = c.getMcafArray(dxdt);
  double *arrdHcafdt = c.getHcafArray(dxdt);
  double *arrdMcasdt = c.getMcasArray(dxdt);
  double *arrdHcasdt = c.getHcasArray(dxdt);
  double *arrdMk1dt = c.getMk1Array(dxdt);
  double *arrdHk1dt = c.getHk1Array(dxdt);
  double *arrdMkadt = c.getMkaArray(dxdt);
  double *arrdHkadt = c.getHkaArray(dxdt);
  double *arrdMkfdt = c.getMkfArray(dxdt);
  double *arrdMhdt = c.getMhArray(dxdt);
  double *arrdAdt = c.getAArray(dxdt);
  double *arrdPdt = c.getPArray(dxdt);
  double *arrdMdt = c.getMArray(dxdt);
  double *arrdGdt = c.getGArray(dxdt);
  double *arrdHdt = c.getHArray(dxdt);

  const int numOfNeurons = c.numOfNeurons;
  const int numOfSynapses = c.numOfSynapses;
#if USE_OPENMP
  #pragma omp parallel default(shared)
#endif
  {
    for (int i = 0; i < numOfNeurons; i++) {
      using namespace std;
      const NeuronConstants &n = c.getNeuronConstantAt(i);
      const double V = arrV[i];
#if USE_OPENMP
      #pragma omp task
#endif
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
                       isyns(V, arrP, arrM, arrG, c.getAllSynapseConstants(), *(n.incoming), n.incoming->size())
        ) / n.capacitance;
      }
#if USE_OPENMP
      #pragma omp task
#endif
      {
        // Calculate dMk2dt
        arrdMk2dt[i] = dMk2dt(V, arrMk2[i]);
        // Calculate dMpdt
        arrdMpdt[i] = dMpdt(V, arrMp[i]);
        // Calculate dMnadt
        arrdMnadt[i] = dMnadt(V, arrMna[i]);
        // Calculate dHnadt
        arrdHnadt[i] = dHnadt(V, arrHna[i]);
        // Calculate dMcafdt
        arrdMcafdt[i] = dMcafdt(V, arrMcaf[i]);
        // Calculate dHcafdt
        arrdHcafdt[i] = dHcafdt(V, arrHcaf[i]);
        // Calculate dMcasdt
        arrdMcasdt[i] = dMcasdt(V, arrMcas[i]);
        // Calculate dHcasdt
        arrdHcasdt[i] = dHcasdt(V, arrHcas[i]);
        // Calculate dMk1dt
        arrdMk1dt[i] = dMk1dt(V, arrMk1[i]);
        // Calculate dHk1dt
        arrdHk1dt[i] = dHk1dt(V, arrHk1[i]);
        // Calculate dMkadt
        arrdMkadt[i] = dMkadt(V, arrMka[i]);
        // Calculate dHkadt
        arrdHkadt[i] = dHkadt(V, arrHka[i]);
        // Calculate dMkfdt
        arrdMkfdt[i] = dMkfdt(V, arrMkf[i]);
        // Calculate dMhdt
        arrdMhdt[i] = dMhdt(V, arrMh[i]);
      }
    }

    for (int j = 0; j < numOfSynapses; j++) {
      using namespace std;
      const SynapseConstants &s = c.getSynapseConstantAt(j);
      const int sourceNeuronIndex = s.source;
      const NeuronConstants &n = c.getNeuronConstantAt(sourceNeuronIndex);
      const double V = arrV[sourceNeuronIndex];
#if USE_OPENMP
      #pragma omp task
#endif
      {
        // Calculate dPdt
        // TODO Cache the result from loop above to save time
        arrdPdt[j] = ica(
          icaf(n.gbarcaf, arrMcaf[sourceNeuronIndex], arrHcaf[sourceNeuronIndex], V, n.eca),
          icas(n.gbarcas, arrMcas[sourceNeuronIndex], arrHcas[sourceNeuronIndex], V, n.eca),
          arrA[j]
        ) - s.buffering * arrP[j];
      }
#if USE_OPENMP
      #pragma omp task
#endif
      {
        // Calculate dAdt
        arrdAdt[j] = (1.0e-10 / (1 + exp(-100.0 * (V + 0.02))) - arrA[j]) / 0.2;
        // Calculate dMdt
        arrdMdt[j] = (0.1 + 0.9 / (1 + exp(-1000.0 * (V + 0.04))) - arrM[j]) / 0.2;
        // Calculate dGdt
        arrdGdt[j] = -arrG[j] / s.tauDecay + arrH[j];
        // Calculate dHdt
        arrdHdt[j] = -arrH[j] / s.tauRise + (V > s.thresholdV ? s.h0 : 0);
      }
    }
  };
}
