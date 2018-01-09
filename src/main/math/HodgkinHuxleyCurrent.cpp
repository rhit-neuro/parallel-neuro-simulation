#include <cmath>
#include "ODE.h"

using namespace ode::hodgkinhuxley::current;
using namespace state;

double ode::hodgkinhuxley::current::ina(double gbarna, double mna, double hna, double V, double Ena) {
  return gbarna * pow(mna, 3) * hna * (V - Ena);
}

double ode::hodgkinhuxley::current::ip(double gbarp, double mp, double V, double Ena) {
  return gbarp * mp * (V - Ena);
}

double ode::hodgkinhuxley::current::icaf(double gbarcaf, double mcaf, double hcaf, double V, double Eca) {
  return gbarcaf * pow(mcaf, 3) * hcaf * (V - Eca);
}

double ode::hodgkinhuxley::current::icas(double gbarcas, double mcas, double hcas, double V, double Eca) {
  return gbarcas * pow(mcas, 3) * hcas * (V - Eca);
}

double ode::hodgkinhuxley::current::ik1(double gbark1, double mk1, double hk1, double V, double Ek) {
  return gbark1 * pow(mk1, 2) * hk1 * (V - Ek);
}

double ode::hodgkinhuxley::current::ik2(double gbark2, double mk2, double V, double Ek) {
  return gbark2 * pow(mk2, 2) * (V - Ek);
}

double ode::hodgkinhuxley::current::ika(double gbarka, double mka, double hka, double V, double Ek) {
  return gbarka * pow(mka, 2) * hka * (V - Ek);
}

double ode::hodgkinhuxley::current::ikf(double gbarkf, double mkf, double V, double Ek) {
  return gbarkf * mkf * (V - Ek);
}

double ode::hodgkinhuxley::current::ih(double gbarh, double mh, double V, double Eh) {
  return gbarh * pow(mh, 2) * (V - Eh);
}

double ode::hodgkinhuxley::current::il(double gbarl, double V, double El) {
  return gbarl * (V - El);
}

double ode::hodgkinhuxley::current::ica(double icaf, double icas, double A) {
  return fmax(0, -(icaf + icas + A));
}

double ode::hodgkinhuxley::current::isyn(double V, double P, double M, double g, SynapseConstants *allSynapses,
                                         ProtobufRepeatedInt32 &ownSynapses, int numOfOwnSynapses) {
  double result = 0;
  // TODO Investigate the formula expressed here. It's not the same as in the paper
  #pragma omp parallel for reduction(+:result)
  for (int i = 0; i < numOfOwnSynapses; i++) {
    const int synapseIndex = ownSynapses[i];
    const SynapseConstants &s = allSynapses[synapseIndex];
    const double Esyn = s.esyn;
    const double gbarsyng = s.gbarsyng;
    const double gbarsyns = s.gbarsyns;
    const double cGraded = s.cGraded;
    const double tauDecay = s.tauDecay;
    const double tauRise = s.tauRise;
    const double P3 = pow(P, 3);
    double isyng = gbarsyng * P3 * (V - Esyn) * (cGraded + P3);
    // TODO Investigate: magic number t0
    const double t0 = 0;
    const double tPeak = t0 + (tauDecay * tauRise * log(tauDecay/tauRise)) / (tauDecay - tauRise);
    // TODO Investigate: why
    const double fsyns = 1 / (exp(-(tPeak - t0)/tauDecay) + exp(-(tPeak - t0)/tauRise));
    const double isyns = (V - Esyn) * M * gbarsyns * fsyns * g;
    result += (isyng + isyns);
  }
  return result;
}
