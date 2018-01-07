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
  } Neuron;

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
  } Synapse;

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

    private:
      // Arrays for constant variables and initial state
      Neuron *neurons;
      Synapse *synapses;
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
