#include "ODE.h"

using namespace state;
ConfigAdapter c = ConfigAdapter::getInstance();

void ode::hodgkinhuxley::calculateNextState(const storage_type &x, storage_type &dxdt, double t) {
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


}
