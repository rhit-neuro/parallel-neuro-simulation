#include <iostream>
#include <fstream>
#include "ArgParser.h"

using namespace std;

bool argparser::parse(int argc, char **argv, po::variables_map &vm) {
  po::options_description desc("Allowed options");

  desc.add_options()
    ("help", "produce help message")
    ("input-file,i", po::value<string>()->required(), "input file location")
    ("input-format,if", po::value<string>()->default_value("JSON"), "input file format (JSON, default JSON)")
    ("logging-config,lc", po::value<string>(), "logging configuration file location")
#if USE_OPENMP
    ("num-threads,t", po::value<unsigned int>()->default_value(0), "Specify number of threads OpenMP should use. Specify 0 to let OpenMP automatically decide")
#endif
    ("output-file,o", po::value<string>()->required(), "output file location")
    ("output-format,of", po::value<string>()->default_value("CSV"), "output file format (CSV, default CSV)")
    ("output-precision,op", po::value<int>()->default_value(7), "number of decimal points to be displayed/written to output")
#if INCLUDE_LUT_SUPPORT
    ("use-lut,lut", po::value<bool>()->default_value(false), "Whether to use LUT during computation")
#endif
    ("verbose-level,vl", po::value<int>()->default_value(1), "set verbose level printed to output stream (1 - 3, default 1)")
	("config-file,c", po::value<string>(), "config file location")
  ;

  po::store(po::parse_command_line(argc, reinterpret_cast<const char * const *>(argv), desc), vm);
  // If "help" exists, then help message should be printed, and the rest of the program should be aborted
  if (vm.count("help")) {
    cout << desc << "\n";
    return false;
  }

  // If "config-file" exits, then read options from the config file. Options passed through the CLI will override
  // those which are in the config file
  if (vm.count("config-file")) {
    const auto &configFile = vm["config-file"].as<string>();
	ifstream configIStream;
    configIStream.open (configFile);
	po::store(po::parse_config_file(configIStream, desc), vm);
  }

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
