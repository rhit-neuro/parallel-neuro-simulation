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

  /**
   * Specifies that opt1 and opt2 are conflicting options.
   * Throws a logic_error if both are specified in vm.
   * @param vm Variable map to check
   * @param opt1 First option as a string
   * @param opt2 Second option as a string
   */
  void conflicting_options(const po::variables_map& vm,
                         const char* opt1, const char* opt2);

  /**
   * Specifies that required_option is required for for_what.
   * Throws a logic_error if for_what exists without required_option.
   * @param vm Variable map to check
   * @param for_what option with a dependency
   * @param required_option opiton for_what depends on
   */
  void option_dependency(const po::variables_map& vm,
                        const char* for_what, const char* required_option);
};


#endif //PARALLEL_NEURON_SIMULATION_ARGPARSER_H
