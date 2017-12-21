#ifndef PARALLEL_NEURON_SIMULATION_TIMELOGGER_H
#define PARALLEL_NEURON_SIMULATION_TIMELOGGER_H


class TimeLogger {
  public:
    static TimeLogger& getInstance() {
      TimeLogger* instancePtr;
      #pragma omp critical(singleton_init_timelogger)
      {
        static TimeLogger loggerInstance;
        instancePtr = &loggerInstance;
      }

      return *instancePtr;
    }

    void recordProgramStartTime();
    void recordProgramEndTime();
    void recordLoadConfigStartTime();
    void recordLoadConfigEndTime();

  private:
    TimeLogger();
};


#endif //PARALLEL_NEURON_SIMULATION_TIMELOGGER_H
