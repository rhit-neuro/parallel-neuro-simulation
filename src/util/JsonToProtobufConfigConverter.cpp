#include "JsonToProtobufConfigConverter.h"

#include <fstream>
#include <iostream>
#include <map>
#include <json-v3.0.0.hpp>

using json = nlohmann::json;
using namespace input_config;

double JsonToProtobufConfigConverter::getRandomNormal(double mean, double deviation) {
  return mean;
}

Config JsonToProtobufConfigConverter::readConfig(string &input_file) {
  // Load from file
  Config c;
  std::ifstream infile(input_file);
  json j;
  infile >> j;
  infile.close();
  int synapseIndex = 0;

  Config_Solver *solver = c.mutable_solver();
  solver->set_starttime(j["configuration"]["solver"]["startTime"]);
  solver->set_endtime(j["configuration"]["solver"]["endTime"]);
  solver->set_abserror(j["configuration"]["solver"]["absoluteError"]);
  solver->set_relerror(j["configuration"]["solver"]["relativeError"]);
  solver->set_solver(j["configuration"]["solver"]["solver"]);

  // Size neuron array properly
  int numNeurons = j["configuration"]["neurons"].size();
  for (int i = 0; i < numNeurons; ++i) {
    c.add_neurons();
  }
  //std::cout << c.neurons_size();

  // Associate name with index in
  std::map<string, int> nameToIndex;
  int index = 0;
  for (json::iterator it = j["configuration"]["neurons"].begin();
       it != j["configuration"]["neurons"].end();
       ++it, ++index) {
    nameToIndex[it.key()] = index;
  }

  // Print out map contents
  /*for (const auto &p : nameToIndex) {
      std::cout << "m[" << p.first << "] = " << p.second << '\n';
  }*/

  index = 0;
  for (json::iterator it = j["configuration"]["neurons"].begin();
       it != j["configuration"]["neurons"].end();
       ++it, ++index) {
    Config_Neuron *n = c.mutable_neurons(nameToIndex[it.key()]);
    if (j["configuration"]["neuronParameters"].find(it.value()["neuronType"]) !=
        j["configuration"]["neuronParameters"].end()) {
      n->set_gbarna(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarna"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarna_dev"]
      ));
      n->set_gbarp(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarp"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarp_dev"]
      ));
      n->set_gbarcaf(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarcaf"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarcaf_dev"]
      ));
      n->set_gbarcas(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarcas"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarcas_dev"]
      ));
      n->set_gbark1(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbark1"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbark1_dev"]
      ));
      n->set_gbark2(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbark2"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbark2_dev"]
      ));
      n->set_gbarka(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarka"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarka_dev"]
      ));
      n->set_gbarkf(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarkf"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarkf_dev"]
      ));
      n->set_gbarh(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarh"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarh_dev"]
      ));
      n->set_gbarl(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarl"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["gbarl_dev"]
      ));
      n->set_ena(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["ena"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["ena_dev"]
      ));
      n->set_eca(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["eca"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["eca_dev"]
      ));
      n->set_ek(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["ek"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["ek_dev"]
      ));
      n->set_eh(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["eh"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["eh_dev"]
      ));
      n->set_el(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["el"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["el_dev"]
      ));
      n->set_capacitance(getRandomNormal(
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["capacitance"],
        j["configuration"]["neuronParameters"][it.value().value("neuronType", "")]["capacitance_dev"]
      ));
      n->set_ivoltage(it.value().value("iVoltage", 0.0));
      n->set_imk2(it.value().value("imk2", 0.0));
      n->set_imp(it.value().value("imp", 0.0));
      n->set_imna(it.value().value("imna", 0.0));
      n->set_ihna(it.value().value("ihna", 0.0));
      n->set_imcaf(it.value().value("imcaf", 0.0));
      n->set_ihcaf(it.value().value("ihcaf", 0.0));
      n->set_imcas(it.value().value("imcas", 0.0));
      n->set_ihcas(it.value().value("ihcas", 0.0));
      n->set_imk1(it.value().value("imk1", 0.0));
      n->set_ihk1(it.value().value("ihk1", 0.0));
      n->set_imka(it.value().value("imka", 0.0));
      n->set_ihka(it.value().value("ihka", 0.0));
      n->set_imkf(it.value().value("imkf", 0.0));
      n->set_imh(it.value().value("imh", 0.0));
      for (json::iterator synIt = it.value()["synapses"].begin(); synIt != it.value()["synapses"].end(); ++synIt) {
        for (int synNum = 0; synNum < synIt.value().size(); ++synNum) {
          Config_Synapse *s = c.add_synapses();
          if (j["configuration"]["synapseParameters"].find(synIt.key()) !=
              j["configuration"]["synapseParameters"].end()) {
            //std::cout << "Source name: " << synIt.value().at(synNum) << ", " << nameToIndex[synIt.value().at(synNum)] << '\n';
            s->set_source(nameToIndex[synIt.value().at(synNum)]);
            //std::cout << s->source() << '\n';
            s->set_gbarsyng(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["gbarsyng"],
              j["configuration"]["synapseParameters"][synIt.key()]["gbarsyng_dev"]
            ));
            s->set_gbarsyns(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["gbarsyns"],
              j["configuration"]["synapseParameters"][synIt.key()]["gbarsyns_dev"]
            ));
            s->set_esyn(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["esyn"],
              j["configuration"]["synapseParameters"][synIt.key()]["esyn_dev"]
            ));
            s->set_buffering(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["buffering"],
              j["configuration"]["synapseParameters"][synIt.key()]["buffering_dev"]
            ));
            s->set_h0(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["h0"],
              j["configuration"]["synapseParameters"][synIt.key()]["h0_dev"]
            ));
            s->set_thresholdv(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["thresholdV"],
              j["configuration"]["synapseParameters"][synIt.key()]["thresholdV_dev"]
            ));
            s->set_taudecay(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["tauDecay"],
              j["configuration"]["synapseParameters"][synIt.key()]["tauDecay_dev"]
            ));
            s->set_taurise(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["tauRise"],
              j["configuration"]["synapseParameters"][synIt.key()]["tauRise_dev"]
            ));
            s->set_cgraded(getRandomNormal(
              j["configuration"]["synapseParameters"][synIt.key()]["cGraded"],
              j["configuration"]["synapseParameters"][synIt.key()]["cGraded_dev"]
            ));
            s->set_ia(j["configuration"]["synapseParameters"][synIt.key()]["iA"]);
            s->set_ip(j["configuration"]["synapseParameters"][synIt.key()]["iP"]);
            s->set_im(j["configuration"]["synapseParameters"][synIt.key()]["iM"]);
            s->set_ig(j["configuration"]["synapseParameters"][synIt.key()]["ig"]);
            s->set_ih(j["configuration"]["synapseParameters"][synIt.key()]["ih"]);
          }
          n->add_incoming(synapseIndex);
          synapseIndex++;
        }
      }
    } else {
      std::cerr << "Invalid neuron configuration parameters for neuron " << it.key() << std::endl;
      exit(0);
    }
  }

  //std::cout << c.DebugString() << endl;

  return c;
}
