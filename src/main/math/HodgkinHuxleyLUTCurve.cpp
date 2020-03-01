#if INCLUDE_LUT_SUPPORT
#include "LUT.h"
#include "ODE.h"

using namespace lut;

inline double finf(double a, double b, double v) {
  const double V = - a * (v + b);
  return lutSingleton->interpolate(V, FINF);
  //return 1.0 / (1.0 + exp(a * (v + b)));
}

inline double fhinf(double v) {
  const double V = 180 * (v + 0.047);
  return lutSingleton->interpolate(V, FHINF);
  //return 1.0 / (1.0 + 2.0 * exp(180.0 * temp) + exp(500.0 * temp));
}

inline double invcosh(double a, double b, double v) {
  const double V = a * (b + v);
  return lutSingleton->interpolate(V, INVCOSH);
}

inline double tau(double a, double b, double c, double d, double v) {
  return c + d * finf(a, b, v);
  //return c + d / (1.0 + exp(a * (v + b)));
}

inline double tauhna(double v) {
  return 0.004 + 0.006 * finf(500.0, 0.028, v) + 0.01 * invcosh(300, 0.027, v);
  //return 0.004 + 0.006 / (1.0 + exp(500.0 * (v + 0.028))) + 0.01 / cosh(300 * (v + 0.027));
}

inline double taumkf(double v) {
  return 1.5 + 8.0 * finf(-100.0, 0.022, v) - 2.2 * invcosh(100.0, 0.04, v);
  //return 1.5 + 8.0 / (1 + exp(-100.0 * (v + 0.022))) - 2.2 / cosh(100.0 * (v + 0.04));
}

inline double taumcaf(double v) {
  return 0.011 + 0.024 * invcosh(-330.0, 0.0467, v);
  //return 0.011 + 0.024 / cosh(-330.0 * (v + 0.0467));
}

double ode::hodgkinhuxley_lut::curve::dMk2dt(double V, double mk2) {
  return (finf(-83.0, 0.02, V) - mk2) / tau(200.0, 0.035, 0.057, 0.043, V);
}

double ode::hodgkinhuxley_lut::curve::dMpdt(double V, double mp) {
  return (finf(-120.0, 0.039, V) - mp) / tau(400.0, 0.057, 0.01, 0.2, V);
}

double ode::hodgkinhuxley_lut::curve::dMnadt(double V, double mna) {
  return (finf(-150.0, 0.029, V) - mna) / 0.0001;
}

double ode::hodgkinhuxley_lut::curve::dHnadt(double V, double hna) {
  return (finf(500.0, 0.030, V) - hna) / tauhna(V);
}

double ode::hodgkinhuxley_lut::curve::dMcafdt(double V, double mcaf) {
  return (finf(-600.0, 0.0467, V) - mcaf) / taumcaf(V);
}

double ode::hodgkinhuxley_lut::curve::dHcafdt(double V, double hcaf) {
  return (finf(350.0, 0.0555, V) - hcaf) / tau(270.0, 0.055, 0.06, 0.31, V);
}

double ode::hodgkinhuxley_lut::curve::dMcasdt(double V, double mcas) {
  return (finf(-420.0, 0.0472, V) - mcas) / tau(-400.0, 0.0487, 0.005, 0.134, V);
}

double ode::hodgkinhuxley_lut::curve::dHcasdt(double V, double hcas) {
  return (finf(360.0, 0.055, V) - hcas) / tau(-250.0, 0.043, 0.2, 5.25, V);
}

double ode::hodgkinhuxley_lut::curve::dMk1dt(double V, double mk1) {
  return (finf(-143.0, 0.021, V) - mk1) / tau(150.0, 0.016, 0.001, 0.011, V);
}

double ode::hodgkinhuxley_lut::curve::dHk1dt(double V, double hk1) {
  return (finf(111.0, 0.028, V) - hk1) / tau(-143.0, 0.013, 0.5, 0.2, V);
}

double ode::hodgkinhuxley_lut::curve::dMkadt(double V, double mka) {
  return (finf(-130.0, 0.044, V) - mka) / tau(200.0, 0.03, 0.005, 0.011, V);
}

double ode::hodgkinhuxley_lut::curve::dHkadt(double V, double hka) {
  return (finf(160.0, 0.063, V) - hka) / tau(-300.0, 0.055, 0.026, 0.0085, V);
}

double ode::hodgkinhuxley_lut::curve::dMkfdt(double V, double mkf) {
  return (finf(-100.0, 0.022, V) - mkf) / taumkf(V);
}

double ode::hodgkinhuxley_lut::curve::dMhdt(double V, double mh) {
  return (fhinf(V) - mh) / tau(-100.0, 0.073, 0.7, 1.7, V);
}
#endif
