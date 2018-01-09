#include "ConfigAdapter.h"


using namespace state;

double * ConfigAdapter::getVArray(storage_type &allVariables) {
  return &(allVariables[offset_V]);
}

double * ConfigAdapter::getMk2Array(storage_type &allVariables) {
  return &(allVariables[offset_mk2]);
}

double * ConfigAdapter::getMpArray(storage_type &allVariables) {
  return &(allVariables[offset_mp]);
}

double * ConfigAdapter::getMnaArray(storage_type &allVariables) {
  return &(allVariables[offset_mna]);
}

double * ConfigAdapter::getHnaArray(storage_type &allVariables) {
  return &(allVariables[offset_hna]);
}

double * ConfigAdapter::getMcafArray(storage_type &allVariables) {
  return &(allVariables[offset_mcaf]);
}

double * ConfigAdapter::getHcafArray(storage_type &allVariables) {
  return &(allVariables[offset_hcaf]);
}

double * ConfigAdapter::getMcasArray(storage_type &allVariables) {
  return &(allVariables[offset_mcas]);
}

double * ConfigAdapter::getHcasArray(storage_type &allVariables) {
  return &(allVariables[offset_hcas]);
}

double * ConfigAdapter::getMk1Array(storage_type &allVariables) {
  return &(allVariables[offset_mk1]);
}

double * ConfigAdapter::getHk1Array(storage_type &allVariables) {
  return &(allVariables[offset_hk1]);
}

double * ConfigAdapter::getMkaArray(storage_type &allVariables) {
  return &(allVariables[offset_mka]);
}

double * ConfigAdapter::getHkaArray(storage_type &allVariables) {
  return &(allVariables[offset_hka]);
}

double * ConfigAdapter::getMkfArray(storage_type &allVariables) {
  return &(allVariables[offset_mkf]);
}

double * ConfigAdapter::getMhArray(storage_type &allVariables) {
  return &(allVariables[offset_mh]);
}

double * ConfigAdapter::getAArray(storage_type &allVariables) {
  return &(allVariables[offset_A]);
}

double * ConfigAdapter::getPArray(storage_type &allVariables) {
  return &(allVariables[offset_P]);
}

double * ConfigAdapter::getMArray(storage_type &allVariables) {
  return &(allVariables[offset_M]);
}

double * ConfigAdapter::getGArray(storage_type &allVariables) {
  return &(allVariables[offset_g]);
}

double * ConfigAdapter::getHArray(storage_type &allVariables) {
  return &(allVariables[offset_h]);
}

NeuronConstants &ConfigAdapter::getNeuronConstantsOf(int neuronIndex) {
  return neurons[neuronIndex];
}

SynapseConstants &ConfigAdapter::getSynapseConstantsOf(int synapseIndex) {
  return synapses[synapseIndex];
}
