#ifndef __JSONTOCONFIG_H
#define __JSONTOCONFIG_H


#include "proto/protobuf_config.pb.h"
#include <string>

using namespace std;
using namespace protobuf_config;

class JsonToProtobufConfigConverter {
  public:
    Config readConfig(string &input_file);

  private:
    double getRandomNormal(double mean, double deviation);
};


#endif
