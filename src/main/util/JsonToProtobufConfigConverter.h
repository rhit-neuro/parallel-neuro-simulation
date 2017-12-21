#ifndef __JSONTOCONFIG_H
#define __JSONTOCONFIG_H


#include "proto/input_config.pb.h"
#include <string>

using namespace std;
using namespace input_config;

class JsonToProtobufConfigConverter {
  public:
    Config readConfig(string &input_file);

  private:
    double getRandomNormal(double mean, double deviation);
};


#endif
