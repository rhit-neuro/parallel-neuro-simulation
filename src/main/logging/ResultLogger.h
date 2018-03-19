#ifndef PARALLEL_NEURON_SIMULATION_RESULTLOGGER_H
#define PARALLEL_NEURON_SIMULATION_RESULTLOGGER_H


#include "AsyncBuffer.h"

class ResultLogger {
  public:
    static ResultLogger& getInstance() {
      ResultLogger* instancePtr;
#if USE_OPENMP
      #pragma omp critical(singleton_init_resultlogger)
#endif
      {
        static ResultLogger loggerInstance;
        instancePtr = &loggerInstance;
      }
      return *instancePtr;
    }

    void setNumberOfNeurons(int numOfNeurons);
    void recordV(double t, const double *V);

  private:
    /**
     * If setNumberOfNeurons is called, inited is true, and further calls to setNumberOfNeurons should have no effect
     */
    bool inited;
    AsyncBuffer* buffer;

    ResultLogger();
};


#endif //PARALLEL_NEURON_SIMULATION_RESULTLOGGER_H
