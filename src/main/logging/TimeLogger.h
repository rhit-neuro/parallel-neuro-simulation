#ifndef PARALLEL_NEURON_SIMULATION_TIMELOGGER_H
#define PARALLEL_NEURON_SIMULATION_TIMELOGGER_H


#include <chrono>

using namespace std::chrono;

class TimeLogger {
  public:
    static TimeLogger& getInstance() {
      TimeLogger* instancePtr;
#if USE_OPENMP
      #pragma omp critical(singleton_init_timelogger)
#endif
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
    void recordCalculationStartTime();
    void recordCalculationEndTime();

    void printSummary();

  private:
    steady_clock::time_point programStartTime;
    steady_clock::time_point programEndTime;
    steady_clock::time_point loadConfigStartTime;
    steady_clock::time_point loadConfigEndTime;
    steady_clock::time_point calculationStartTime;
    steady_clock::time_point calculationEndTime;

    TimeLogger();
};


#endif //PARALLEL_NEURON_SIMULATION_TIMELOGGER_H
