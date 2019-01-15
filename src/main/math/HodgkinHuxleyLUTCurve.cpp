#if INCLUDE_LUT_SUPPORT
#include "LUT.h"
#include "ODE.h"

using namespace lut;

double dCommon(double V, double x, CurveSelect inf, CurveSelect tau) {
  double finfLookupResult, tauLookupResult;
  finfLookupResult = lutSingleton->interpolate(V, inf);
  tauLookupResult = lutSingleton->interpolate(V, tau);
  return (finfLookupResult - x) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dMk2dt(double V, double mk2) {
  return dCommon(V, mk2, M_F_K2, M_T_K2);
}

double ode::hodgkinhuxley_lut::curve::dMpdt(double V, double mp) {
  return dCommon(V, mp, M_F_P, M_T_P);
}

double ode::hodgkinhuxley_lut::curve::dMnadt(double V, double mna) {
  double finfLookupResult, tauLookupResult;
  finfLookupResult = lutSingleton->interpolate(V, M_F_NA);
  // tauLookupResult = lutSingleton->interpolate(V, M_T_NA);
  tauLookupResult = 0.0001;
  return (finfLookupResult - mna) / tauLookupResult;
}

double ode::hodgkinhuxley_lut::curve::dHnadt(double V, double hna) {
  return dCommon(V, hna, H_F_NA, H_T_NA);
}

double ode::hodgkinhuxley_lut::curve::dMcafdt(double V, double mcaf) {
  return dCommon(V, mcaf, M_F_CAF, M_T_CAF);
}

double ode::hodgkinhuxley_lut::curve::dHcafdt(double V, double hcaf) {
  return dCommon(V, hcaf, H_F_CAF, H_T_CAF);
}

double ode::hodgkinhuxley_lut::curve::dMcasdt(double V, double mcas) {
  return dCommon(V, mcas, M_F_CAS, M_T_CAS);
}

double ode::hodgkinhuxley_lut::curve::dHcasdt(double V, double hcas) {
  return dCommon(V, hcas, H_F_CAS, H_T_CAS);
}

double ode::hodgkinhuxley_lut::curve::dMk1dt(double V, double mk1) {
  return dCommon(V, mk1, M_F_K1, M_T_K1);
}

double ode::hodgkinhuxley_lut::curve::dHk1dt(double V, double hk1) {
  return dCommon(V, hk1, H_F_K1, H_T_K1);
}

double ode::hodgkinhuxley_lut::curve::dMkadt(double V, double mka) {
  return dCommon(V, mka, M_F_KA, M_T_KA);
}

double ode::hodgkinhuxley_lut::curve::dHkadt(double V, double hka) {
  return dCommon(V, hka, H_F_KA, H_T_KA);
}

double ode::hodgkinhuxley_lut::curve::dMkfdt(double V, double mkf) {
  return dCommon(V, mkf, M_F_KF, M_T_KF);
}

double ode::hodgkinhuxley_lut::curve::dMhdt(double V, double mh) {
  return dCommon(V, mh, M_F_H, M_T_H);
}
#endif
