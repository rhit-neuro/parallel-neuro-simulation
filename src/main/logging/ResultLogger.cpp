#include "ResultLogger.h"


ResultLogger::ResultLogger() {
  this->inited = false;
}

void ResultLogger::setNumberOfNeurons(int numOfNeurons) {
  if (this->inited) {
    std::cerr << "ResultLogger::setNumberOfNeurons called more than once" << "\n";
    return; // This method should not be called more than once
  }
  this->buffer = new AsyncBuffer(numOfNeurons, (std::string &) "1231231123", 5, 1);
  this->inited = true;
}

void ResultLogger::recordV(const double t, const double *V) {
  this->buffer->writeData(V);
}
