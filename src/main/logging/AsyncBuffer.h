#ifndef __ASYNCBUFFER_H
#define __ASYNCBUFFER_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <pthread.h>

struct thread_data {
  int lineSize;
  int precision;
  int lines;
  std::ofstream ofs;
  double *message;
};

class AsyncBuffer {
  public:
    AsyncBuffer(int size, std::string &output_filename, int precision, int verbosity);
    ~AsyncBuffer();
    void writeData(const double *data);

  private:
    void startThread();

    thread_data td;
    pthread_t thread;
    pthread_attr_t attr;
    int size;
    int decimalPrecision;
    int index;
    bool *full;// = {false, false};
    int threadRunning;
    int currentBuffer;
    double **buffers;
    // For handling verbosity
    float printTimestep;
    float printAfterTime;
};

#endif
