#ifndef PARALLEL_NEURON_SIMULATION_RESULTLOGGER_H
#define PARALLEL_NEURON_SIMULATION_RESULTLOGGER_H


class ResultLogger {
  public:
    static ResultLogger& getInstance() {
      ResultLogger* instancePtr;
      #pragma omp critical(singleton_init_resultlogger)
      {
        static ResultLogger loggerInstance;
        instancePtr = &loggerInstance;
      }
      return *instancePtr;
    }

    void setNumberOfNeurons(int numOfNeurons);
    void recordV(double t, const double *V);

  private:
    ResultLogger();
};


#endif //PARALLEL_NEURON_SIMULATION_RESULTLOGGER_H
