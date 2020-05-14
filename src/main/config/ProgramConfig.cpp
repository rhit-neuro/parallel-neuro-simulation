#include "ProgramConfig.h"

using namespace config;
using namespace config::offsets;
using namespace std;

void ProgramConfig::loadProtobufConfig(protobuf_config::Config &pc) {
  protoConfigPtr = &pc;
  auto &s = pc.solver();
  absoluteError = s.abserror();
  relativeError = s.relerror();
  startTime = s.starttime();
  endTime = s.endtime();

  numOfNeurons = pc.neurons_size();
  numOfSynapses = pc.synapses_size();
  numOfNeuronVariables = numOfNeurons * NUM_OF_NEURON_VARIABLES;
  numOfSynapseVariables = numOfSynapses * NUM_OF_SYNAPSE_VARIABLES;

  initializeNeuronOffsets();
  initializeSynapseOffsets();

  neurons = static_cast<NeuronConstants *>(malloc(numOfNeurons * sizeof(NeuronConstants)));
  if (!neurons) {
    cerr << "Failed to allocate memory for the NeuronConstants array" << "\n";
    exit(1);
  }
  initializeNeuronConstantProperties();

  synapses = static_cast<SynapseConstants *>(malloc(numOfSynapses * sizeof(SynapseConstants)));
  if (!synapses) {
    cerr << "Failed to allocate memory for the SynapseConstants array" << "\n";
    exit(1);
  }
  initializeSynapseConstantProperties();
}

storage_type & ProgramConfig::getInitialStateValues() {
  initialStateValues = storage_type(static_cast<unsigned long>(numOfNeuronVariables + numOfSynapseVariables));
  initializeNeuronVariables();
  initializeSynapseVariables();
  return initialStateValues;
}

void ProgramConfig::initializeNeuronOffsets() {
  offset_V = OFF_V * numOfNeurons;
  offset_mk2 = OFF_mk2 * numOfNeurons;
  offset_mp = OFF_mp * numOfNeurons;
  offset_mna = OFF_mna * numOfNeurons;
  offset_hna = OFF_hna * numOfNeurons;
  offset_mcaf = OFF_mcaf * numOfNeurons;
  offset_hcaf = OFF_hcaf * numOfNeurons;
  offset_mcas = OFF_mcas * numOfNeurons;
  offset_hcas = OFF_hcas * numOfNeurons;
  offset_mk1 = OFF_mk1 * numOfNeurons;
  offset_hk1 = OFF_hk1 * numOfNeurons;
  offset_mka = OFF_mka * numOfNeurons;
  offset_hka = OFF_hka * numOfNeurons;
  offset_mkf = OFF_mkf * numOfNeurons;
  offset_mh = OFF_mh * numOfNeurons;
}

void ProgramConfig::initializeSynapseOffsets() {
  offset_A = numOfNeuronVariables + OFF_A * numOfSynapses;
  offset_P = numOfNeuronVariables + OFF_P * numOfSynapses;
  offset_M = numOfNeuronVariables + OFF_M * numOfSynapses;
  offset_g = numOfNeuronVariables + OFF_g * numOfSynapses;
  offset_h = numOfNeuronVariables + OFF_h * numOfSynapses;
}

void ProgramConfig::initializeNeuronConstantProperties() {
  protobuf_config::Config &pc = *protoConfigPtr;
  for (int i = 0; i < numOfNeurons; i++) {
    const auto &protoNeuron = pc.neurons(i);
    NeuronConstants *neuronPtr = neurons + i;
    neuronPtr->gbarna = protoNeuron.gbarna();
    neuronPtr->gbarp = protoNeuron.gbarp();
    neuronPtr->gbarcaf = protoNeuron.gbarcaf();
    neuronPtr->gbarcas = protoNeuron.gbarcas();
    neuronPtr->gbark1 = protoNeuron.gbark1();
    neuronPtr->gbark2 = protoNeuron.gbark2();
    neuronPtr->gbarka = protoNeuron.gbarka();
    neuronPtr->gbarkf = protoNeuron.gbarkf();
    neuronPtr->gbarh = protoNeuron.gbarh();
    neuronPtr->gbarl = protoNeuron.gbarl();
    neuronPtr->ena = protoNeuron.ena();
    neuronPtr->eca = protoNeuron.eca();
    neuronPtr->ek = protoNeuron.ek();
    neuronPtr->eh = protoNeuron.eh();
    neuronPtr->el = protoNeuron.el();
    neuronPtr->capacitance = protoNeuron.capacitance();
    neuronPtr->incoming = const_cast<ProtobufRepeatedInt32 *>(&(protoNeuron.incoming()));
  }
}

void ProgramConfig::initializeSynapseConstantProperties() {
  protobuf_config::Config &pc = *protoConfigPtr;
  for (int i = 0; i < numOfSynapses; i++) {
    const auto &protoSynapse = pc.synapses(i);
    SynapseConstants *synapsePtr = synapses + i;
    synapsePtr->source = protoSynapse.source();
    synapsePtr->gbarsyng = protoSynapse.gbarsyng();
    synapsePtr->gbarsyns = protoSynapse.gbarsyns();
    synapsePtr->esyn = protoSynapse.esyn();
    synapsePtr->buffering = protoSynapse.buffering();
    synapsePtr->h0 = protoSynapse.h0();
    synapsePtr->thresholdV = protoSynapse.thresholdv();

	const double tauDecay = protoSynapse.taudecay();
	const double tauRise =  protoSynapse.taurise();
    synapsePtr->tauDecay = tauDecay;
    synapsePtr->tauRise = tauRise;
	
    synapsePtr->cGraded = protoSynapse.cgraded();

    const double tPeak = (tauDecay * tauRise * log(tauDecay/tauRise)) / (tauDecay - tauRise);
    synapsePtr->fsyns = 1 / (exp(-(tPeak)/tauDecay) + exp(-(tPeak)/tauRise));
  }
}

void ProgramConfig::initializeNeuronVariables() {
  protobuf_config::Config &pc = *protoConfigPtr;
  for (int i = 0; i < numOfNeurons; i++) {
    const auto &protoNeuron = pc.neurons(i);
    initialStateValues[offset_V + i] = protoNeuron.ivoltage();
    initialStateValues[offset_mk2 + i] = protoNeuron.imk2();
    initialStateValues[offset_mp + i] = protoNeuron.imp();
    initialStateValues[offset_mna + i] = protoNeuron.imna();
    initialStateValues[offset_hna + i] = protoNeuron.ihna();
    initialStateValues[offset_mcaf + i] = protoNeuron.imcaf();
    initialStateValues[offset_hcaf + i] = protoNeuron.ihcaf();
    initialStateValues[offset_mcas + i] = protoNeuron.imcas();
    initialStateValues[offset_hcas + i] = protoNeuron.ihcas();
    initialStateValues[offset_mk1 + i] = protoNeuron.imk1();
    initialStateValues[offset_hk1 + i] = protoNeuron.ihk1();
    initialStateValues[offset_mka + i] = protoNeuron.imka();
    initialStateValues[offset_hka + i] = protoNeuron.ihka();
    initialStateValues[offset_mkf + i] = protoNeuron.imkf();
    initialStateValues[offset_mh + i] = protoNeuron.imh();
  }
}

void ProgramConfig::initializeSynapseVariables() {
  protobuf_config::Config &pc = *protoConfigPtr;
  for (int i = 0; i < numOfSynapses; i++) {
    const auto &protoSynapse = pc.synapses(i);
    initialStateValues[offset_A + i] = protoSynapse.ia();
    initialStateValues[offset_P + i] = protoSynapse.ip();
    initialStateValues[offset_M + i] = protoSynapse.im();
    initialStateValues[offset_g + i] = protoSynapse.ig();
    initialStateValues[offset_h + i] = protoSynapse.ih();
  }
}
