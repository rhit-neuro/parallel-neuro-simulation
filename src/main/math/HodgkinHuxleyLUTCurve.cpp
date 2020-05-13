#if INCLUDE_LUT_SUPPORT
#include "LUT.h"
#include "ODE.h"

using namespace lut;

inline double finf(CurveSelect cs, double v) {
  //const double V = - a * (v + b);
  return lutSingleton->interpolate(v, cs);
  //return 1.0 / (1.0 + exp(a * (v + b)));
}

inline double fhinf(double v) {
  //const double V = 180 * (v + 0.047);
  return lutSingleton->interpolate(v, FHINF);
  //return 1.0 / (1.0 + 2.0 * exp(180.0 * temp) + exp(500.0 * temp));
}

inline double invcosh(CurveSelect cs, double v) {
  //const double V = a * (b + v);
  return lutSingleton->interpolate(v, cs);
}

inline double tau(CurveSelect cs, double c, double d, double v) {
  return c + d * finf(cs, v);
  //return c + d / (1.0 + exp(a * (v + b)));
}

inline double tauhna(double v) {
  return 0.004 + 0.006 * finf(Hna_TAU, v) + 0.01 * invcosh(Hna_ICOS, v);
  //return 0.004 + 0.006 / (1.0 + exp(500.0 * (v + 0.028))) + 0.01 / cosh(300 * (v + 0.027));
}

inline double taumkf(double v) {
  return 1.5 + 8.0 * finf(Mkf_TAU, v) - 2.2 * invcosh(Mkf_ICOS, v);
  //return 1.5 + 8.0 / (1 + exp(-100.0 * (v + 0.022))) - 2.2 / cosh(100.0 * (v + 0.04));
}

inline double taumcaf(double v) {
  return 0.011 + 0.024 * invcosh(Mcaf_ICOS, v);
  //return 0.011 + 0.024 / cosh(-330.0 * (v + 0.0467));
}

double ode::hodgkinhuxley_lut::curve::dMk2dt(double V, double mk2) {
  return (finf(Mk2_FINF, V) - mk2) / tau(Mk2_TAU, 0.057, 0.043, V);
}

double ode::hodgkinhuxley_lut::curve::dMpdt(double V, double mp) {
  return (finf(Mp_FINF, V) - mp) / tau(Mp_TAU, 0.01, 0.2, V);
}

double ode::hodgkinhuxley_lut::curve::dMnadt(double V, double mna) {
  return (finf(Mna_FINF, V) - mna) / 0.0001;
}

double ode::hodgkinhuxley_lut::curve::dHnadt(double V, double hna) {
  return (finf(Hna_FINF, V) - hna) / tauhna(V);
}

double ode::hodgkinhuxley_lut::curve::dMcafdt(double V, double mcaf) {
  return (finf(Mcaf_FINF, V) - mcaf) / taumcaf(V);
}

double ode::hodgkinhuxley_lut::curve::dHcafdt(double V, double hcaf) {
  return (finf(Hcaf_FINF, V) - hcaf) / tau(Hcaf_TAU, 0.06, 0.31, V);
}

double ode::hodgkinhuxley_lut::curve::dMcasdt(double V, double mcas) {
  return (finf(Mcas_FINF, V) - mcas) / tau(Mcas_TAU, 0.005, 0.134, V);
}

double ode::hodgkinhuxley_lut::curve::dHcasdt(double V, double hcas) {
  return (finf(Hcas_FINF, V) - hcas) / tau(Hcas_TAU, 0.2, 5.25, V);
}

double ode::hodgkinhuxley_lut::curve::dMk1dt(double V, double mk1) {
  return (finf(Mk1_FINF, V) - mk1) / tau(Mk1_TAU, 0.001, 0.011, V);
}

double ode::hodgkinhuxley_lut::curve::dHk1dt(double V, double hk1) {
  return (finf(Hk1_FINF, V) - hk1) / tau(Hk1_TAU, 0.5, 0.2, V);
}

double ode::hodgkinhuxley_lut::curve::dMkadt(double V, double mka) {
  return (finf(Mka_FINF, V) - mka) / tau(Mka_TAU, 0.005, 0.011, V);
}

double ode::hodgkinhuxley_lut::curve::dHkadt(double V, double hka) {
  return (finf(Hka_FINF, V) - hka) / tau(Hka_TAU, 0.026, 0.0085, V);
}

double ode::hodgkinhuxley_lut::curve::dMkfdt(double V, double mkf) {
  return (finf(Mkf_FINF, V) - mkf) / taumkf(V);
}

double ode::hodgkinhuxley_lut::curve::dMhdt(double V, double mh) {
  return (fhinf(V) - mh) / tau(Mh_TAU, 0.7, 1.7, V);
}
#endif