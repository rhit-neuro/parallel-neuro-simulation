#include <cmath>
#include "ODE.h"

double ode::hodgkinhuxley::curve::finf(double a, double b, double v) {
  return 1.0 / (1.0 + exp(a * (v + b)));
}

double ode::hodgkinhuxley::curve::fhinf(double v) {
  const double temp = v + 0.047;
  return 1.0 / (1.0 + 2.0 * exp(180.0 * temp) + exp(500.0 * temp));
}

double ode::hodgkinhuxley::curve::tau(double a, double b, double c, double d, double v) {
  return c + d / (1.0 + exp(a * (v + b)));
}

double ode::hodgkinhuxley::curve::tauhna(double v) {
  return 0.004 + 0.006 / (1.0 + exp(500.0 * (v + 0.028))) + 0.01 / cosh(300 * (v + 0.027));
}

double ode::hodgkinhuxley::curve::taumkf(double v) {
  return 1.5 + 8.0 / (1 + exp(-100.0 * (v + 0.022))) - 2.2 / cosh(100.0 * (v + 0.04));
}

double ode::hodgkinhuxley::curve::taumcaf(double v) {
  return 0.011 + 0.024 / cosh(-330.0 * (v + 0.0467));
}
