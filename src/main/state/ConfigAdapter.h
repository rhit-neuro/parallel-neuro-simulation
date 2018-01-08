#ifndef PARALLEL_NEURON_SIMULATION_CONFIGURATION_H
#define PARALLEL_NEURON_SIMULATION_CONFIGURATION_H


#include <proto/protobuf_config.pb.h>

namespace state {
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
    ProtobufRepeatedInt32 &incoming;
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

  class ConfigAdapter {
      // TODO Come up with better names
    public:
      // Public fields
      double absoluteError;
      double relativeError;
      int numOfNeurons;
      int numOfSynapses;
      int numOfNeuronVariables;
      int numOfSynapseVariables;

      // Public methods
      explicit ConfigAdapter(protobuf_config::Config &protoConfig);
      ~ConfigAdapter();
      double *getInitialStateValues();

      // Utility methods to get subarraies
      double * getVArray(double * allVariables);
      double * getmk2Array(double * allVariables);
      double * getMpArray(double * allVariables);
      double * getMnaArray(double * allVariables);
      double * getHnaArray(double * allVariables);
      double * getMcafArray(double * allVariables);
      double * getHcafArray(double * allVariables);
      double * getMcasArray(double * allVariables);
      double * getHcasArray(double * allVariables);
      double * getMk1Array(double * allVariables);
      double * getHk1Array(double * allVariables);
      double * getMkaArray(double * allVariables);
      double * getHkaArray(double * allVariables);
      double * getMkfArray(double * allVariables);
      double * getMhArray(double * allVariables);
      double * getAArray(double * allVariables);
      double * getPArray(double * allVariables);
      double * getMArray(double * allVariables);
      double * getGArray(double * allVariables);
      double * getHArray(double * allVariables);

    private:
      // Arrays for constant variables and initial state
      NeuronConstants *neurons;
      SynapseConstants *synapses;
      double *initialStateValues;

      // Neuron variable offsets
      int offset_V;
      int offset_mk2;
      int offset_mp;
      int offset_mna;
      int offset_hna;
      int offset_mcaf;
      int offset_hcaf;
      int offset_mcas;
      int offset_hcas;
      int offset_mk1;
      int offset_hk1;
      int offset_mka;
      int offset_hka;
      int offset_mkf;
      int offset_mh;

      // Synapse variable offsets
      int offset_A;
      int offset_P;
      int offset_M;
      int offset_g;
      int offset_h;

      // Private methods
      void initializeNeuronOffsets();
      void initializeSynapseOffsets();
      void initializeNeuronConstantProperties(protobuf_config::Config &protoConfig);
      void initializeSynapseConstantProperties(protobuf_config::Config &protoConfig);
      void initializeNeuronVariables(protobuf_config::Config &protoConfig);
      void initializeSynapseVariables(protobuf_config::Config &protoConfig);
  };

}

#endif //PARALLEL_NEURON_SIMULATION_CONFIGURATION_H
