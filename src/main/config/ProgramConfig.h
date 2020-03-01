#ifndef PARALLEL_NEURON_SIMULATION_CONFIGURATION_H
#define PARALLEL_NEURON_SIMULATION_CONFIGURATION_H


#include <proto/protobuf_config.pb.h>
#include "../global/GlobalDefinitions.h"

using namespace global_definitions;

namespace config {
  typedef ::google::protobuf::RepeatedField<::google::protobuf::int32> ProtobufRepeatedInt32;

  typedef struct {
    double gbarna;
    double gbarp;
    double gbarcaf;
    double gbarcas;
    double gbark1;
    double gbark2;
    double gbarka;
    double gbarkf;
    double gbarh;
    double gbarl;
    double ena;
    double eca;
    double ek;
    double eh;
    double el;
    double capacitance;
    ProtobufRepeatedInt32 *incoming;
  } NeuronConstants;

  typedef struct {
    int source;
    double gbarsyng;
    double gbarsyns;
    double esyn;
    double buffering;
    double h0;
    double thresholdV;
    double tauDecay;
    double tauRise;
    double cGraded;
    double fsyns;
  } SynapseConstants;

  namespace offsets {
    // Offsets for neurons
    const short OFF_V = 0;
    const short OFF_mk2 = 1;
    const short OFF_mp = 2;
    const short OFF_mna = 3;
    const short OFF_hna = 4;
    const short OFF_mcaf = 5;
    const short OFF_hcaf = 6;
    const short OFF_mcas = 7;
    const short OFF_hcas = 8;
    const short OFF_mk1 = 9;
    const short OFF_hk1 = 10;
    const short OFF_mka = 11;
    const short OFF_hka = 12;
    const short OFF_mkf = 13;
    const short OFF_mh = 14;

    const short NUM_OF_NEURON_VARIABLES = 15;

    // Offsets for synapses
    const short OFF_A = 0;
    const short OFF_P = 1;
    const short OFF_M = 2;
    const short OFF_g = 3;
    const short OFF_h = 4;

    const short NUM_OF_SYNAPSE_VARIABLES = 5;
  }

  class ProgramConfig {
      // TODO Come up with better names
    public:
      // Static methods
      static ProgramConfig& getInstance() {
        // Initialization will be done before library call, so no need for critical section
        static ProgramConfig configInstance;
        return configInstance;
      }

      // Public fields
      double absoluteError{0.0};
      double relativeError{0.0};
      double startTime{0.0};
      double endTime{0.0};
      int numOfNeurons{0};
      int numOfSynapses{0};
      int numOfNeuronVariables{0};
      int numOfSynapseVariables{0};

      // Public methods
      void loadProtobufConfig(protobuf_config::Config &protoConfig);
      storage_type & getInitialStateValues();
      NeuronConstants& getNeuronConstantAt(int neuronIndex);
      SynapseConstants& getSynapseConstantAt(int synapseIndex);
      SynapseConstants* getAllSynapseConstants();

      // Utility methods to get subarraies
      double * getVArray(storage_type &allVariables);
      double * getMk2Array(storage_type &allVariables);
      double * getMpArray(storage_type &allVariables);
      double * getMnaArray(storage_type &allVariables);
      double * getHnaArray(storage_type &allVariables);
      double * getMcafArray(storage_type &allVariables);
      double * getHcafArray(storage_type &allVariables);
      double * getMcasArray(storage_type &allVariables);
      double * getHcasArray(storage_type &allVariables);
      double * getMk1Array(storage_type &allVariables);
      double * getHk1Array(storage_type &allVariables);
      double * getMkaArray(storage_type &allVariables);
      double * getHkaArray(storage_type &allVariables);
      double * getMkfArray(storage_type &allVariables);
      double * getMhArray(storage_type &allVariables);
      double * getAArray(storage_type &allVariables);
      double * getPArray(storage_type &allVariables);
      double * getMArray(storage_type &allVariables);
      double * getGArray(storage_type &allVariables);
      double * getHArray(storage_type &allVariables);

    private:
      // Arrays for constant variables and initial state
      protobuf_config::Config *protoConfigPtr{nullptr};
      NeuronConstants *neurons{nullptr};
      SynapseConstants *synapses{nullptr};
      storage_type initialStateValues;

      // Neuron variable offsets
      int offset_V{0};
      int offset_mk2{0};
      int offset_mp{0};
      int offset_mna{0};
      int offset_hna{0};
      int offset_mcaf{0};
      int offset_hcaf{0};
      int offset_mcas{0};
      int offset_hcas{0};
      int offset_mk1{0};
      int offset_hk1{0};
      int offset_mka{0};
      int offset_hka{0};
      int offset_mkf{0};
      int offset_mh{0};

      // Synapse variable offsets
      int offset_A{0};
      int offset_P{0};
      int offset_M{0};
      int offset_g{0};
      int offset_h{0};

      // Private methods
      ProgramConfig() = default;
      void initializeNeuronOffsets();
      void initializeSynapseOffsets();
      void initializeNeuronConstantProperties();
      void initializeSynapseConstantProperties();
      void initializeNeuronVariables();
      void initializeSynapseVariables();
  };

}

#endif //PARALLEL_NEURON_SIMULATION_CONFIGURATION_H
