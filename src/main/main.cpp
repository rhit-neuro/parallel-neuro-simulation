#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/numeric/odeint.hpp>
#include <proto/protobuf_config.pb.h>
#include "global/GlobalDefinitions.h"

#include "util/ArgParser.h"
#include "logging/TimeLogger.h"
#include "factory/Factory.h"
#include "util/JsonToProtobufConfigConverter.h"
#include "logging/AsyncBuffer.h"
#include "state/ConfigAdapter.h"

using namespace global_definitions;
using namespace boost::numeric::odeint;
using namespace std;

int main(int argc, char** argv) {
  TimeLogger tLogger = TimeLogger::getInstance();
  tLogger.recordProgramStartTime();

  po::variables_map vm;
  if (!argparser::parse(argc, argv, vm)) {
    return 1;
  }

  const auto &inputFile = vm["input-file"].as<string>();
  const auto &outputFile = vm["output-file"].as<string>();

  JsonToProtobufConfigConverter converter;
  Config config = converter.readConfig(const_cast<string &>(inputFile));
  state::ConfigAdapter c = state::ConfigAdapter::getInstance();
  try {
    c.loadProtobufConfig(config);
  } catch (exception &e) {
    cerr << e.what() << endl;
    return 1;
  }

  auto buffer = new AsyncBuffer(config.neurons_size() + 1, const_cast<string &>(outputFile));

  sequential::ode_system_function *equation = factory::equation::getEquation();

  integrate_adaptive(
    make_controlled(
      c.absoluteError,
      c.relativeError,
      runge_kutta_dopri5<storage_type>()
    ),
    equation,
    c.getInitialStateValues(),
    c.startTime,
    c.endTime,
    0.1,
    [&](const storage_type &x, const double t) {
      storage_type toWrite(x);
      toWrite.insert(toWrite.begin(), t);
      buffer->writeData(&(toWrite[0]));
    }
  );

  cout << boost::filesystem::current_path() << endl;

  return 0;
}
