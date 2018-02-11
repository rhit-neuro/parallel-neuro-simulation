#include "ProgramConfig.h"


using namespace config;

double * ProgramConfig::getVArray(storage_type &allVariables) {
  return &(allVariables[offset_V]);
}

double * ProgramConfig::getMk2Array(storage_type &allVariables) {
  return &(allVariables[offset_mk2]);
}

double * ProgramConfig::getMpArray(storage_type &allVariables) {
  return &(allVariables[offset_mp]);
}

double * ProgramConfig::getMnaArray(storage_type &allVariables) {
  return &(allVariables[offset_mna]);
}

double * ProgramConfig::getHnaArray(storage_type &allVariables) {
  return &(allVariables[offset_hna]);
}

double * ProgramConfig::getMcafArray(storage_type &allVariables) {
  return &(allVariables[offset_mcaf]);
}

double * ProgramConfig::getHcafArray(storage_type &allVariables) {
  return &(allVariables[offset_hcaf]);
}

double * ProgramConfig::getMcasArray(storage_type &allVariables) {
  return &(allVariables[offset_mcas]);
}

double * ProgramConfig::getHcasArray(storage_type &allVariables) {
  return &(allVariables[offset_hcas]);
}

double * ProgramConfig::getMk1Array(storage_type &allVariables) {
  return &(allVariables[offset_mk1]);
}

double * ProgramConfig::getHk1Array(storage_type &allVariables) {
  return &(allVariables[offset_hk1]);
}

double * ProgramConfig::getMkaArray(storage_type &allVariables) {
  return &(allVariables[offset_mka]);
}

double * ProgramConfig::getHkaArray(storage_type &allVariables) {
  return &(allVariables[offset_hka]);
}

double * ProgramConfig::getMkfArray(storage_type &allVariables) {
  return &(allVariables[offset_mkf]);
}

double * ProgramConfig::getMhArray(storage_type &allVariables) {
  return &(allVariables[offset_mh]);
}

double * ProgramConfig::getAArray(storage_type &allVariables) {
  return &(allVariables[offset_A]);
}

double * ProgramConfig::getPArray(storage_type &allVariables) {
  return &(allVariables[offset_P]);
}

double * ProgramConfig::getMArray(storage_type &allVariables) {
  return &(allVariables[offset_M]);
}

double * ProgramConfig::getGArray(storage_type &allVariables) {
  return &(allVariables[offset_g]);
}

double * ProgramConfig::getHArray(storage_type &allVariables) {
  return &(allVariables[offset_h]);
}

NeuronConstants& ProgramConfig::getNeuronConstantAt(int neuronIndex) {
  return neurons[neuronIndex];
}

SynapseConstants& ProgramConfig::getSynapseConstantAt(int synapseIndex) {
  return synapses[synapseIndex];
}

SynapseConstants* ProgramConfig::getAllSynapseConstants(){
  return synapses;
}
