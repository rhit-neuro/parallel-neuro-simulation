#include <iostream>

#include <boost/filesystem.hpp>
#include <proto/input_config.pb.h>
#include "global/GlobalDefinitions.h"

#include "util/ArgParser.h"
#include "logging/TimeLogger.h"
#include "factory/Factory.h"

using namespace global_definitions;

int main(int argc, char** argv) {
  TimeLogger tLogger = TimeLogger::getInstance();
  tLogger.recordProgramStartTime();


  sequential::ode_system_function *equation = factory::equation::getEquation();

  ArgParser::parse(argc, (const char **) argv);
  input_config::Config config;

  std::cout << boost::filesystem::current_path() << std::endl;

  return 0;
}
