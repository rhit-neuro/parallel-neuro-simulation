#if INCLUDE_LUT_SUPPORT
#include "ODE.h"
#include <lut_support-a7d4c9fa7d6a4c1a5c1494d29d99617b392c8255/lut_support.h>


double ode::hodgkinhuxley_lut::curve::dMk2dt(double V, double mk2) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - mk2) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMpdt(double V, double mp) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - mp) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMnadt(double V, double mna) {
  double finfLookupResult;
  findLUTValues(V, finfLookupResult);
  return (finfLookupResult - mna) / 0.0001;
}

double ode::hodgkinhuxley_lut::curve::dHnadt(double V, double hna) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - hna) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMcafdt(double V, double mcaf) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - mcaf) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dHcafdt(double V, double hcaf) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - hcaf) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMcasdt(double V, double mcas) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - mcas) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dHcasdt(double V, double hcas) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - hcas) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMk1dt(double V, double mk1) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - mk1) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dHk1dt(double V, double hk1) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - hk1) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMkadt(double V, double mka) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - mka) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dHkadt(double V, double hka) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - hka) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMkfdt(double V, double mkf) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - mkf) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMhdt(double V, double mh) {
  double finfLookupResult, tauLookupResult;
  findLUTValues(V, finfLookupResult);
  findLUTValues(V, tauLookupResult);
  return (finfLookupResult - mh) / tauLookupResult;
}
#endif
