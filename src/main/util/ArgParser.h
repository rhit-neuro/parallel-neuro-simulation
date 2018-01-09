#ifndef PARALLEL_NEURON_SIMULATION_ARGPARSER_H
#define PARALLEL_NEURON_SIMULATION_ARGPARSER_H


#include "../global/GlobalDefinitions.h"

using namespace global_definitions;

namespace argparser {
  /**
   * Parse the arguments to the program when it starts
   * @param argc Argument count, same as argc for main
   * @param argv Argument values, same as argv for main
   * @param vm Variable map to be populated
   * @return true if valid options are collected; false otherwise
   */
  bool parse(int argc, char **argv, po::variables_map &vm);
};


#endif //PARALLEL_NEURON_SIMULATION_ARGPARSER_H
