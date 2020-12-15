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

// CMake will create NDEBUG when we're not in a Debug CMAKE_RELEASE_TYPE
#ifndef NDEBUG
#if RISCV
#include "logging/hpm_counters.cxx"
#include "rocc/lut_support.h"
#include "rocc/fixed_integrator.h"
#endif
#endif

using namespace global_definitions;
using namespace boost::numeric::odeint;
using namespace std;

#ifndef NDEBUG
#if RISCV
unsigned long accCalls() //This has to be its own function; otherwise it just gives us 0
{
  unsigned long retVal; // Probably register versus stack versus heap allocation differences...
  getCount(retVal);
  return retVal;
}
#endif
#endif

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

  #ifndef NDEBUG
  #if RISCV
  resetCount();
  handle_stats(INIT);
  #endif
  #endif

  tLogger.recordCalculationStartTime();

  int steps = 0;
  double step_size = 0.00025;
  double half_step_size = step_size / 2.0;
  double step_size_div6 = step_size / 6.0;
  storage_type dx1 = storage_type(static_cast<unsigned long>(x.size()));
  storage_type dx2 = storage_type(static_cast<unsigned long>(x.size()));
  storage_type dx3 = storage_type(static_cast<unsigned long>(x.size()));
  storage_type dx4 = storage_type(static_cast<unsigned long>(x.size()));
  storage_type x_temp = storage_type(static_cast<unsigned long>(x.size()));
  uint result;
  
  while (timeData[0] < c.endTime){
  
  	observer(x, timeData[0]);
  	
  	//k1
  	equation(x, dx1, timeData[0]);
  	
  	//k2
  	for (int i = 0; i < x.size(); i++){
  
  		#if RISCV
  		integrateHalfStep(result, *(uint *)&dx1[i], *(uint *)&x[i]);
  		x_temp[i] = *(float *)&result;
  		#else
  		x_temp[i] = x[i] + half_step_size * dx1[i];
  		#endif
  	}
  	equation(x_temp, dx2, timeData[0] + half_step_size);
  	
  	//k3
  	for (int i = 0; i < x.size(); i++){
  		
  		#if RISCV
  		integrateHalfStep(result, *(uint *)&dx2[i], *(uint *)&x[i]);
  		x_temp[i] = *(float *)&result;
  		#else 
  		x_temp[i] = x[i] + half_step_size * dx2[i];
  		#endif
  	}
  	equation(x_temp, dx3, timeData[0] + half_step_size);
  	
  	//k4
  	for (int i = 0; i < x.size(); i++){
  		
  		#if RISCV
  		integrateWholeStep(result, *(uint *)&dx3[i], *(uint *)&x[i]);
  		x_temp[i] = *(float *)&result;
  		#else
  		x_temp[i] = x[i] + step_size * dx3[i];
  		#endif
  	}
  	equation(x_temp, dx4, timeData[0] + step_size);
  	
  	//x_n+1
  	for (int i = 0; i < x.size(); i++){
  	
  		x[i] += step_size_div6 * (dx1[i] + 2 * dx2[i] + 2 * dx3[i] + dx4[i]);
  	}
  	
  	steps++;
  	timeData[0] = c.startTime + static_cast<double>(steps)*step_size;
  }
  
  /*
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
  */
  // Make an observation at t=c.endTime
  observer(x, timeData[0]);

  tLogger.recordCalculationEndTime();
  
  #ifndef NDEBUG
  #if RISCV
  handle_stats(FINISH);
  printf("%lu LUT instructions called\n", accCalls());
  #endif

  printf("%llu calculateNextState calls\n", ode::hodgkinhuxley::numSteps);
  #endif

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
