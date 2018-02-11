#include <iostream>
#include "TimeLogger.h"


TimeLogger::TimeLogger() = default;

void TimeLogger::recordProgramStartTime() {
  programStartTime = std::chrono::steady_clock::now();
}

void TimeLogger::recordProgramEndTime() {
  programEndTime = std::chrono::steady_clock::now();
}

void TimeLogger::recordLoadConfigStartTime() {
  loadConfigStartTime = std::chrono::steady_clock::now();
}

void TimeLogger::recordLoadConfigEndTime() {
  loadConfigEndTime = std::chrono::steady_clock::now();
}

void TimeLogger::recordCalculationStartTime() {
  calculationStartTime = std::chrono::steady_clock::now();
}

void TimeLogger::recordCalculationEndTime() {
  calculationEndTime = std::chrono::steady_clock::now();
}

void TimeLogger::printSummary() {
  std::cout << "Program run: "
            << duration_cast<microseconds>(programEndTime - programStartTime).count()
            << "ms"
            << "("
            << duration_cast<seconds>(programEndTime - programStartTime).count()
            << "s)"
            << '\n'
            << "Load config run: "
            << duration_cast<microseconds>(loadConfigEndTime - loadConfigStartTime).count()
            << "ms"
            << "("
            << duration_cast<seconds>(loadConfigEndTime - loadConfigStartTime).count()
            << "s)"
            << '\n'
            << "Calculation run: "
            << duration_cast<microseconds>(calculationEndTime - calculationStartTime).count()
            << "ms"
            << "("
            << duration_cast<seconds>(calculationEndTime - calculationStartTime).count()
            << "s)"
            << '\n';
}
