#include <iostream>
#include <fstream>
#include "ArgParser.h"

using namespace std;

bool argparser::parse(int argc, char **argv, po::variables_map &vm) {
  po::options_description desc("Allowed options");

  desc.add_options()
    ("config-file,c", po::value<string>(), "config file location")
    ("help,h", "produce help message")
    ("input-file,i", po::value<string>()->required(), "input file location")
    ("input-format,f", po::value<string>()->default_value("JSON"), "input file format (JSON, default JSON)")
    ("logging-config,g", po::value<string>(), "logging configuration file location")
#if INCLUDE_LUT_SUPPORT
    ("lut-file,u", po::value<string>(), "LUT points file location")
#endif    
#if USE_OPENMP
    ("num-threads,t", po::value<unsigned int>()->default_value(0), "specify number of threads OpenMP should use. Specify 0 to let OpenMP automatically decide")
#endif
    ("output-file,o", po::value<string>()->required(), "output file location")
    ("output-format", po::value<string>()->default_value("CSV"), "output file format (CSV, default CSV)")
    ("output-precision,p", po::value<int>()->default_value(7), "number of decimal points to be displayed/written to output")
#if INCLUDE_LUT_SUPPORT
    ("use-lut,l", "whether to use LUT during computation")
    ("use-soft-lut,s", "whether to use software LUT during computation")
#endif
    ("verbose-level,v", po::value<int>()->default_value(1), "set verbose level printed to output stream (1 - 3, default 1)")
  ;

  po::store(po::parse_command_line(argc, reinterpret_cast<const char * const *>(argv), desc), vm);
  // If "help" exists, then help message should be printed, and the rest of the program should be aborted
  if (vm.count("help") || argc == 1) {
    cout << desc << "\n";
    return false;
  }

  // If "config-file" exits, then read options from the config file. Options passed through the CLI will override
  // those which are in the config file
  if (vm.count("config-file")) {
    const auto &configFile = vm["config-file"].as<string>();
    ifstream configIStream(configFile);
    if (!configIStream) {
      cerr << "Configuration file '" << configFile << "' could not be read\n";
      cerr << "Aborted\n";
      return false;
    }
    po::store(po::parse_config_file(configIStream, desc), vm);
  }

  // Check for conflicting options and options with dependencies
  argparser::conflicting_options(vm, "use-lut", "use-soft-lut");
  argparser::option_dependency(vm, "use-soft-lut", "lut-file");

  try {
    // Call notify(vm) to validate options
    po::notify(vm);
  } catch (po::required_option &e) {
    cerr << e.what() << "\n";
    cerr << "Please add option " << e.get_option_name() << "!" << "\n";
    throw e;
  }

  return true;
}

/* Sourced from https://stackoverflow.com/questions/15577107/sets-of-mutually-exclusive-options-in-boost-program-options
   Function used to check that 'opt1' and 'opt2' are not specified
   at the same time. */
void argparser::conflicting_options(const po::variables_map& vm,
                         const char* opt1, const char* opt2) {
  if (vm.count(opt1) && !vm[opt1].defaulted()
      && vm.count(opt2) && !vm[opt2].defaulted()) {
    throw logic_error(string("Conflicting options '")
                      + opt1 + "' and '" + opt2 + "'.");
    }
}

/* Sourced from https://www.boost.org/doc/libs/1_55_0/libs/program_options/example/real.cpp
   Function used to check that of 'for_what' is specified, then
   'required_option' is specified too. */
void argparser::option_dependency(const po::variables_map& vm,
                        const char* for_what, const char* required_option)
{
    if (vm.count(for_what) && !vm[for_what].defaulted())
        if (vm.count(required_option) == 0 || vm[required_option].defaulted())
            throw logic_error(string("Option '") + for_what 
                              + "' requires option '" + required_option + "'.");
}