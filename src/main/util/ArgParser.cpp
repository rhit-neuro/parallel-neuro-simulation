#include <iostream>
#include "ArgParser.h"

using namespace std;

bool argparser::parse(int argc, char **argv, po::variables_map &vm) {
  po::options_description desc("Allowed options");

  desc.add_options()
    ("help", "produce help message")
    ("input-file,i", po::value<string>()->required(), "input file location")
    ("input-format,if", po::value<string>()->default_value("JSON"), "input file format (JSON, default JSON)")
    ("output-file,o", po::value<string>()->required(), "output file location")
    ("output-format,of", po::value<string>()->default_value("CSV"), "output file format (CSV, default CSV)")
    ("verbose-level,vl", po::value<int>()->default_value(1), "set verbose level printed to output stream (1 - 3, default 1)")
    ("logging-config,lc", po::value<string>(), "logging configuration file location")
    ("num-threads,t", po::value<unsigned int>()->default_value(0), "Specify number of threads OpenMP should use. Specify 0 to let OpenMP automatically decide")
  ;

  po::store(po::parse_command_line(argc, reinterpret_cast<const char * const *>(argv), desc), vm);
  // If "help" exists, then help message should be printed, and the rest of the program should be aborted
  if (vm.count("help")) {
    cout << desc << "\n";
    return false;
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
