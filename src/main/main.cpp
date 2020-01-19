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

using namespace global_definitions;
using namespace boost::numeric::odeint;
using namespace std;

// This function is basically apeing Boost's integrate_const program logic, but flattened, with fewer
// function calls overall. What is surprising is that this is around 15% faster than integrate_const.
template<typename F>
inline void integrate_controlled(config::ProgramConfig &c, sequential::ode_system_function *equation, F observer)
{
  TimeLogger &tLogger = TimeLogger::getInstance();

  storage_type x = c.getInitialStateValues();
  auto myStepper = make_controlled(c.absoluteError, c.relativeError, runge_kutta_dopri5<storage_type>());
  auto timeData = (double*) malloc(2*sizeof(double));
  double observerStep = 0.00025;
  timeData[0] = c.startTime;
  timeData[1] = observerStep;

  tLogger.recordCalculationStartTime();

  int steps = 0;
  while ((timeData[0]+observerStep) <= c.endTime)
  {
    observer(x, timeData[0]);

    // We only want to integrate one observerStep at a time.
    double targetTime = timeData[0] + observerStep;

    while (timeData[0] < targetTime)
    {
      if (targetTime < (timeData[0] + timeData[1]))
        timeData[1] = targetTime - timeData[0]; // guarantee that we hit target_time exactly

      controlled_step_result result; // will be either success or fail
      do
      {
        result = myStepper.try_step(equation, x, timeData[0], timeData[1]);
      } while (result == fail);
    }

    // We do this rather than keeping the timeData[0] values that is set by try_step
    // upon a successful completion of a step because that may compound floating-point error.
    // Boost does the same thing with their integrate_const function.
    steps++;
    timeData[0] = c.startTime + static_cast<double>(steps)*observerStep;
  }
  // Make an observation at t=c.endTime
  observer(x, timeData[0]);

  tLogger.recordCalculationEndTime();
  delete timeData;
}


int main(int argc, char** argv) {
  TimeLogger &tLogger = TimeLogger::getInstance();
  tLogger.recordProgramStartTime();

  po::variables_map vm;
  if (!argparser::parse(argc, argv, vm)) {
    return 0;
  }

  const auto &inputFile = vm["input-file"].as<string>();
  const auto &outputFile = vm["output-file"].as<string>();

  tLogger.recordLoadConfigStartTime();
  JsonToProtobufConfigConverter converter;
  Config config = converter.readConfig(const_cast<string &>(inputFile));
  config::ProgramConfig &c = config::ProgramConfig::getInstance();
  try {
    c.loadProtobufConfig(config);
  } catch (exception &e) {
    cerr << e.what() << endl;
    return 1;
  }
  tLogger.recordLoadConfigEndTime();

  const auto numNeuron = config.neurons_size();
  const int bufferSize = numNeuron + 1;
  const int precision = vm["output-precision"].as<int>();
  const int verbosity = vm["verbose-level"].as<int>();
  auto buffer = new AsyncBuffer(bufferSize, const_cast<string &>(outputFile), precision, verbosity);

  sequential::ode_system_function *equation = factory::equation::getEquation(vm);

  integrate_controlled(c, equation,
    [&](const storage_type &x, const double t)
    {
      storage_type toWrite(bufferSize);
      toWrite[0] = t;
      for (int i = 0; i < bufferSize-1; i++) {
        toWrite[i+1] = x[i];
      }
      buffer->writeData(&(toWrite[0]));
    });

  delete buffer;
  tLogger.recordProgramEndTime();
  tLogger.printSummary();

  return 0;
}
