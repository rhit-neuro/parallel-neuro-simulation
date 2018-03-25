#include "AsyncBuffer.h"

#define NUMBER_OF_BUFFERS 2
#define BUFFER_SPACE 100


void *printFile(void *arg) {
  struct thread_data *my_data;
  my_data = (struct thread_data *) arg;
  //std::cout << "Line Size : " << my_data->lineSize <<std::endl;
  //std::cout << "Number of lines : " << my_data->lines <<std::endl;
  //std::cout << "message: "<< my_data->message[0]<<std::endl;
  const int precision = my_data->precision;
  int index = 0;
  for (int i = 0; i < my_data->lines; i++) {
    my_data->ofs << std::setprecision(precision) << my_data->message[index];
    index++;
    for (int j = 1; j < my_data->lineSize; j++) {
      my_data->ofs << "," << std::setprecision(precision) << my_data->message[index];
      index++;
    }
    my_data->ofs << std::endl;
  }
  pthread_exit(NULL);
}

AsyncBuffer::AsyncBuffer(int size, std::string &output_filename, int precision) {
  this->size = size;
  this->decimalPrecision = precision;
  this->td.ofs.open(output_filename);
  // Initialize and set thread joinable
  pthread_attr_init(&(this->attr));
  pthread_attr_setdetachstate(&(this->attr), PTHREAD_CREATE_JOINABLE);

  this->threadRunning = -1;
  this->currentBuffer = 0;
  this->index = 0;
  this->full = (bool *) malloc(NUMBER_OF_BUFFERS * sizeof(bool));
  this->buffers = (double **) malloc(NUMBER_OF_BUFFERS * sizeof(double *));
  for (int i = 0; i < NUMBER_OF_BUFFERS; i++) {
    this->buffers[i] = (double *) malloc(BUFFER_SPACE * size * sizeof(double));
    this->full[i] = false;
  }
}

AsyncBuffer::~AsyncBuffer() {
  void *status;
  if (this->threadRunning >= 0) {
    pthread_join(this->thread, &status);
    this->full[this->threadRunning] = false;
    this->threadRunning = -1;
  }
  //make sure all buffers all are emptied at deconstruction time, since clearing the buffers takes less time
  for (int i = 0; i < NUMBER_OF_BUFFERS; i++) {
    if (this->full[i]) {
      this->startThread();
      pthread_join(this->thread, &status);
      this->full[this->threadRunning] = false;
      this->threadRunning = -1;
    }
  }
  if (this->index > 0) {
    this->td.lineSize = this->size;
    this->td.precision = this->decimalPrecision;
    this->td.lines = this->index / this->size;
    double *data = (double *) malloc(this->index * size * sizeof(double));
    for (int i = 0; i < this->index; ++i) {
      data[i] = this->buffers[this->currentBuffer][i];
    }
    this->td.message = data;
    int rc = pthread_create(&this->thread, &attr, printFile, (void *) &td);
    if (rc) {
      std::cout << "Error:unable to create thread," << rc << std::endl;
      exit(-1);
    }
    pthread_join(this->thread, &status);
  }
  for (int i = 0; i < NUMBER_OF_BUFFERS; i++) {
    delete this->buffers[i];
  }
  delete this->buffers;
  this->td.ofs.close();
}

void AsyncBuffer::writeData(const double *data) {
  //check if thread is running
  std::cout << std::setprecision(this->decimalPrecision) << data[0] << std::endl;
  if (this->threadRunning == this->currentBuffer) {
    //check if we have room to write data
    if (this->full[this->currentBuffer]) {
      //we have no room, so we must stall
      void *status;
      pthread_join(this->thread, &status);
      this->full[this->threadRunning] = false;
      this->threadRunning = -1;
      this->startThread(); //Start next thread if we can
    }
  }

  int checkValue = this->index + this->size;
  for (int i = 0; this->index < checkValue; i++) {
    this->buffers[this->currentBuffer][this->index] = data[i];
    this->index++;
  }
  if (index == BUFFER_SPACE * this->size) {
    this->index = 0;
    this->full[this->currentBuffer] = true;
    this->currentBuffer++;
    if (this->currentBuffer == NUMBER_OF_BUFFERS) {
      this->currentBuffer = 0;
    }
    this->startThread();
  }
}

void AsyncBuffer::startThread() {
  if (this->threadRunning < 0) {
    for (int i = 0; i < NUMBER_OF_BUFFERS; i++) {
      if (this->full[i]) {
        this->threadRunning = i;
        this->td.lineSize = this->size;
        this->td.precision = this->decimalPrecision;
        this->td.lines = BUFFER_SPACE * 1;
        this->td.message = this->buffers[i];
        int rc = pthread_create(&this->thread, &attr, printFile, (void *) &td);
        if (rc) {
          std::cout << "Error:unable to create thread," << rc << std::endl;
          exit(-1);
        }
        return;
      }
    }
  }
}
