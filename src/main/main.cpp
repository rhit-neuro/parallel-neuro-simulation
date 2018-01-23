#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/openmp/openmp.hpp>
#include <proto/protobuf_config.pb.h>
#include "global/GlobalDefinitions.h"

#include "util/ArgParser.h"
#include "logging/TimeLogger.h"
#include "factory/Factory.h"
#include "util/JsonToProtobufConfigConverter.h"
#include "logging/AsyncBuffer.h"
#include "config/ProgramConfig.h"

using namespace global_definitions;
using namespace boost::numeric::odeint;
using namespace std;

int main(int argc, char** argv) {
  TimeLogger &tLogger = TimeLogger::getInstance();
  tLogger.recordProgramStartTime();

  po::variables_map vm;
  if (!argparser::parse(argc, argv, vm)) {
    return 1;
  }

  const auto &inputFile = vm["input-file"].as<string>();

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
  const auto bufferSize = numNeuron + 1;

  const double START_TIME = 0.0;
  const double END_TIME = 1.0;
  const int NUM_OF_RUNS = 3;

  cout << "With buffer writing" << "\n\n";
  {
    // parallelSingleTaskOutside
    cout << "\n" << "parallelSingleTaskOutside" << endl;
    cerr << "\n" << "parallelSingleTaskOutside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      std::string filename = std::string("parallelSingleTaskOutside") + std::to_string(_);
      auto buffer = new AsyncBuffer(bufferSize, filename);
      tLogger.startArbitraryTimer();
      #pragma omp parallel default(shared)
      {
        #pragma omp single
        {
          integrate_adaptive(
            make_controlled(
              c.absoluteError,
              c.relativeError,
              runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
            ),
            ode::hodgkinhuxley::parallelSingleTaskOutside,
            c.getInitialStateValues(),
            START_TIME,
            END_TIME,
            0.1,
            [&](const storage_type &x, const double t) {
              storage_type toWrite(bufferSize);
              toWrite[0] = t;
              for (int i = 0; i < numNeuron; i++) {
                toWrite[i+1] = x[i];
              }
              buffer->writeData(&(toWrite[0]));
            }
          );
        }
      };
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
      delete buffer;
    }
  }

  {
    // parallelSingleTaskloopTaskOutside
    cout << "\n" << "parallelSingleTaskloopTaskOutside" << endl;
    cerr << "\n" << "parallelSingleTaskloopTaskOutside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      std::string filename = std::string("parallelSingleTaskloopTaskOutside") + std::to_string(_);
      auto buffer = new AsyncBuffer(bufferSize, filename);
      tLogger.startArbitraryTimer();
      #pragma omp parallel default(shared)
      {
        #pragma omp single
        {
          integrate_adaptive(
            make_controlled(
              c.absoluteError,
              c.relativeError,
              runge_kutta_dopri5<
                storage_type, double,
                storage_type, double,
                openmp_range_algebra
              >()
            ),
            ode::hodgkinhuxley::parallelSingleTaskloopTaskOutside,
            c.getInitialStateValues(),
            START_TIME,
            END_TIME,
            0.1,
            [&](const storage_type &x, const double t) {
              storage_type toWrite(bufferSize);
              toWrite[0] = t;
              for (int i = 0; i < numNeuron; i++) {
                toWrite[i+1] = x[i];
              }
              buffer->writeData(&(toWrite[0]));
            }
          );
        }
      };
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
      delete buffer;
    }
  }

  {
    // parallelSingleTaskloopOutside
    cout << "\n" << "parallelSingleTaskloopOutside" << endl;
    cerr << "\n" << "parallelSingleTaskloopOutside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      std::string filename = std::string("parallelSingleTaskloopOutside") + std::to_string(_);
      auto buffer = new AsyncBuffer(bufferSize, filename);
      tLogger.startArbitraryTimer();
      #pragma omp parallel default(shared)
      {
        #pragma omp single
        {
          integrate_adaptive(
            make_controlled(
              c.absoluteError,
              c.relativeError,
              runge_kutta_dopri5<
                storage_type, double,
                storage_type, double,
                openmp_range_algebra
              >()
            ),
            ode::hodgkinhuxley::parallelSingleTaskloopOutside,
            c.getInitialStateValues(),
            START_TIME,
            END_TIME,
            0.1,
            [&](const storage_type &x, const double t) {
              storage_type toWrite(bufferSize);
              toWrite[0] = t;
              for (int i = 0; i < numNeuron; i++) {
                toWrite[i+1] = x[i];
              }
              buffer->writeData(&(toWrite[0]));
            }
          );
        }
      };
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
      delete buffer;
    }
  }

  {
    // parallelForInside
    cout << "\n" << "parallelForInside" << endl;
    cerr << "\n" << "parallelForInside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      std::string filename = std::string("parallelForInside") + std::to_string(_);
      auto buffer = new AsyncBuffer(bufferSize, filename);
      tLogger.startArbitraryTimer();
      integrate_adaptive(
        make_controlled(
          c.absoluteError,
          c.relativeError,
          runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
        ),
        ode::hodgkinhuxley::parallelForInside,
        c.getInitialStateValues(),
        START_TIME,
        END_TIME,
        0.1,
        [&](const storage_type &x, const double t) {
          storage_type toWrite(bufferSize);
          toWrite[0] = t;
          for (int i = 0; i < numNeuron; i++) {
            toWrite[i+1] = x[i];
          }
          buffer->writeData(&(toWrite[0]));
        }
      );
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
      delete buffer;
    }
  }

  {
    // parallelSingleTaskInside
    cout << "\n" << "parallelSingleTaskInside" << endl;
    cerr << "\n" << "parallelSingleTaskInside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      std::string filename = std::string("parallelSingleTaskInside") + std::to_string(_);
      auto buffer = new AsyncBuffer(bufferSize, filename);
      tLogger.startArbitraryTimer();
      integrate_adaptive(
        make_controlled(
          c.absoluteError,
          c.relativeError,
          runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
        ),
        ode::hodgkinhuxley::parallelSingleTaskInside,
        c.getInitialStateValues(),
        START_TIME,
        END_TIME,
        0.1,
        [&](const storage_type &x, const double t) {
          storage_type toWrite(bufferSize);
          toWrite[0] = t;
          for (int i = 0; i < numNeuron; i++) {
            toWrite[i+1] = x[i];
          }
          buffer->writeData(&(toWrite[0]));
        }
      );
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
      delete buffer;
    }
  }

  {
    // parallelSingleTaskloopInside
    cout << "\n" << "parallelSingleTaskloopInside" << endl;
    cerr << "\n" << "parallelSingleTaskloopInside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      std::string filename = std::string("parallelSingleTaskloopInside") + std::to_string(_);
      auto buffer = new AsyncBuffer(bufferSize, filename);
      tLogger.startArbitraryTimer();
      integrate_adaptive(
        make_controlled(
          c.absoluteError,
          c.relativeError,
          runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
        ),
        ode::hodgkinhuxley::parallelSingleTaskloopInside,
        c.getInitialStateValues(),
        START_TIME,
        END_TIME,
        0.1,
        [&](const storage_type &x, const double t) {
          storage_type toWrite(bufferSize);
          toWrite[0] = t;
          for (int i = 0; i < numNeuron; i++) {
            toWrite[i+1] = x[i];
          }
          buffer->writeData(&(toWrite[0]));
        }
      );
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
      delete buffer;
    }
  }

  {
    // parallelSingleTaskloopTaskInside
    cout << "\n" << "parallelSingleTaskloopTaskInside" << endl;
    cerr << "\n" << "parallelSingleTaskloopTaskInside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      std::string filename = std::string("parallelSingleTaskloopTaskInside") + std::to_string(_);
      auto buffer = new AsyncBuffer(bufferSize, filename);
      tLogger.startArbitraryTimer();
      integrate_adaptive(
        make_controlled(
          c.absoluteError,
          c.relativeError,
          runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
        ),
        ode::hodgkinhuxley::parallelSingleTaskloopTaskInside,
        c.getInitialStateValues(),
        START_TIME,
        END_TIME,
        0.1,
        [&](const storage_type &x, const double t) {
          storage_type toWrite(bufferSize);
          toWrite[0] = t;
          for (int i = 0; i < numNeuron; i++) {
            toWrite[i+1] = x[i];
          }
          buffer->writeData(&(toWrite[0]));
        }
      );
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
      delete buffer;
    }
  }

  cout << "Without buffer writing" << "\n\n";
  {
    // parallelForInside
    cout << "\n" << "parallelForInside" << endl;
    cerr << "\n" << "parallelForInside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      tLogger.startArbitraryTimer();
      integrate_adaptive(
        make_controlled(
          c.absoluteError,
          c.relativeError,
          runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
        ),
        ode::hodgkinhuxley::parallelForInside,
        c.getInitialStateValues(),
        START_TIME,
        END_TIME,
        0.1
      );
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
    }
  }

  {
    // parallelSingleTaskInside
    cout << "\n" << "parallelSingleTaskInside" << endl;
    cerr << "\n" << "parallelSingleTaskInside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      tLogger.startArbitraryTimer();
      integrate_adaptive(
        make_controlled(
          c.absoluteError,
          c.relativeError,
          runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
        ),
        ode::hodgkinhuxley::parallelSingleTaskInside,
        c.getInitialStateValues(),
        START_TIME,
        END_TIME,
        0.1
      );
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
    }
  }

  {
    // parallelSingleTaskOutside
    cout << "\n" << "parallelSingleTaskOutside" << endl;
    cerr << "\n" << "parallelSingleTaskOutside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      tLogger.startArbitraryTimer();
      #pragma omp parallel default(shared)
      {
        #pragma omp single
        {
          integrate_adaptive(
            make_controlled(
              c.absoluteError,
              c.relativeError,
              runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
            ),
            ode::hodgkinhuxley::parallelSingleTaskOutside,
            c.getInitialStateValues(),
            START_TIME,
            END_TIME,
            0.1
          );
        }
      };
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
    }
  }

  {
    // parallelSingleTaskloopInside
    cout << "\n" << "parallelSingleTaskloopInside" << endl;
    cerr << "\n" << "parallelSingleTaskloopInside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      tLogger.startArbitraryTimer();
      integrate_adaptive(
        make_controlled(
          c.absoluteError,
          c.relativeError,
          runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
        ),
        ode::hodgkinhuxley::parallelSingleTaskloopInside,
        c.getInitialStateValues(),
        START_TIME,
        END_TIME,
        0.1
      );
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
    }
  }

  {
    // parallelSingleTaskloopOutside
    cout << "\n" << "parallelSingleTaskloopOutside" << endl;
    cerr << "\n" << "parallelSingleTaskloopOutside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      tLogger.startArbitraryTimer();
      #pragma omp parallel default(shared)
      {
        #pragma omp single
        {
          integrate_adaptive(
            make_controlled(
              c.absoluteError,
              c.relativeError,
              runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
            ),
            ode::hodgkinhuxley::parallelSingleTaskloopOutside,
            c.getInitialStateValues(),
            START_TIME,
            END_TIME,
            0.1
          );
        }
      };
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
    }
  }

  {
    // parallelSingleTaskloopTaskInside
    cout << "\n" << "parallelSingleTaskloopTaskInside" << endl;
    cerr << "\n" << "parallelSingleTaskloopTaskInside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      tLogger.startArbitraryTimer();
      integrate_adaptive(
        make_controlled(
          c.absoluteError,
          c.relativeError,
          runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
        ),
        ode::hodgkinhuxley::parallelSingleTaskloopTaskInside,
        c.getInitialStateValues(),
        START_TIME,
        END_TIME,
        0.1
      );
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
    }
  }

  {
    // parallelSingleTaskloopTaskOutside
    cout << "\n" << "parallelSingleTaskloopTaskOutside" << endl;
    cerr << "\n" << "parallelSingleTaskloopTaskOutside" << endl;
    for (int _ = 0; _ < NUM_OF_RUNS; _++) {
      tLogger.startArbitraryTimer();
      #pragma omp parallel default(shared)
      {
        #pragma omp single
        {
          integrate_adaptive(
            make_controlled(
              c.absoluteError,
              c.relativeError,
              runge_kutta_dopri5<
            storage_type, double,
            storage_type, double,
            openmp_range_algebra
          >()
            ),
            ode::hodgkinhuxley::parallelSingleTaskloopTaskOutside,
            c.getInitialStateValues(),
            START_TIME,
            END_TIME,
            0.1
          );
        }
      };
      tLogger.endArbitraryTimer();
      tLogger.printArbitraryTimeDifference();
    }
  }

  return 0;
}
