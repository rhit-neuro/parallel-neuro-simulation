#include <cmath>
#include "ODE.h"


void ode::hodgkinhuxley::calculateNextState(const double &x, double &dxdt, double t) {

}

double ode::hodgkinhuxley::curve::finf(double a, double b, double v) {
  return 1.0 / (1.0 + exp(a * (v + b)));
}

double ode::hodgkinhuxley::curve::fhinf(double v) {
  double firstExp, secondExp;
  // TODO Confirm performance impact of this
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      firstExp = exp(180.0 * (v + 0.047);
    }
    #pragma omp section
    {
      secondExp = exp(500.0 * (v + 0.047));
    };
  };
  return 1.0 / (1.0 + 2.0 * firstExp + secondExp);
}

double ode::hodgkinhuxley::curve::tau(double a, double b, double c, double d, double v) {
  return c + d / (1 + exp(a * (v + b)));
}

double ode::hodgkinhuxley::curve::tauhna(double v) {
  double firstExp, secondExp;
  // TODO Confirm performance impact of this
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      firstExp = exp(500.0 * (v + 0.028));
    }
    #pragma omp section
    {
      secondExp = cosh(300 * (v + 0.027));
    };
  };
  return 0.004 + 0.006 / (1.0 + firstExp) + 0.01 / secondExp;
}

double ode::hodgkinhuxley::curve::taumkf(double v) {
  double firstExp, secondExp;
  // TODO Confirm performance impact of this
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      firstExp = exp(-100.0 * (v + 0.022));
    }
    #pragma omp section
    {
      secondExp = cosh(100.0 * (v + 0.04));
    };
  };
  return 1.5 + 8.0 / (1 + firstExp) + -2.2 / secondExp;
}

double ode::hodgkinhuxley::curve::taumcaf(double v) {
  return 0.011 + 0.024 / cosh(-330.0 * (v + 0.0467));
}
