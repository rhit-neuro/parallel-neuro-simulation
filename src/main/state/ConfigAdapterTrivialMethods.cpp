#include "ConfigAdapter.h"


using namespace state;

double * ConfigAdapter::getVArray(double *allVariables) {
  return allVariables + offset_V;
}

double * ConfigAdapter::getmk2Array(double *allVariables) {
  return allVariables + offset_mk2;
}

double * ConfigAdapter::getMpArray(double *allVariables) {
  return allVariables + offset_mp;
}

double * ConfigAdapter::getMnaArray(double *allVariables) {
  return allVariables + offset_mna;
}

double * ConfigAdapter::getHnaArray(double *allVariables) {
  return allVariables + offset_hna;
}

double * ConfigAdapter::getMcafArray(double *allVariables) {
  return allVariables + offset_mcaf;
}

double * ConfigAdapter::getHcafArray(double *allVariables) {
  return allVariables + offset_hcaf;
}

double * ConfigAdapter::getMcasArray(double *allVariables) {
  return allVariables + offset_mcas;
}

double * ConfigAdapter::getHcasArray(double *allVariables) {
  return allVariables + offset_hcas;
}

double * ConfigAdapter::getMk1Array(double *allVariables) {
  return allVariables + offset_mk1;
}

double * ConfigAdapter::getHk1Array(double *allVariables) {
  return allVariables + offset_hk1;
}

double * ConfigAdapter::getMkaArray(double *allVariables) {
  return allVariables + offset_mka;
}

double * ConfigAdapter::getHkaArray(double *allVariables) {
  return allVariables + offset_hka;
}

double * ConfigAdapter::getMkfArray(double *allVariables) {
  return allVariables + offset_mkf;
}

double * ConfigAdapter::getMhArray(double *allVariables) {
  return allVariables + offset_mh;
}

double * ConfigAdapter::getAArray(double *allVariables) {
  return allVariables + offset_A;
}

double * ConfigAdapter::getPArray(double *allVariables) {
  return allVariables + offset_P;
}

double * ConfigAdapter::getMArray(double *allVariables) {
  return allVariables + offset_M;
}

double * ConfigAdapter::getGArray(double *allVariables) {
  return allVariables + offset_g;
}

double * ConfigAdapter::getHArray(double *allVariables) {
  return allVariables + offset_h;
}
