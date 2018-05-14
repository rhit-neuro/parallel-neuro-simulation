#include "gmock/gmock.h"
#include "../main/util/ArgParser.h"

using namespace std;

char *convert(const string &s) {
   return const_cast<char*>(s.c_str());
}

TEST(ConfigFile, DoesNotExist) {
  po::variables_map vm;
  vector<string> argStrings = {"./main", "--config-file", "not-found.ini"};
  vector<char*> argChars;
  transform(argStrings.begin(), argStrings.end(), back_inserter(argChars), convert);

  EXPECT_FALSE(argparser::parse(argChars.size(), &argChars[0], vm));
}

TEST(ConfigFile, Exists) {
  po::variables_map vm;
  // Note that the path to a config file is relative to the directory this test is run in
  vector<string> argStrings = 
      {"./main", "--config-file", "../../src/test/run-configs/test-config.ini"};
  vector<char*> argChars;
  transform(argStrings.begin(), argStrings.end(), back_inserter(argChars), convert);

  EXPECT_TRUE(argparser::parse(argChars.size(), &argChars[0], vm));
  EXPECT_EQ("from/config/file/in.json", vm["input-file"].as<string>());
  EXPECT_EQ("from/config/file/out.csv", vm["output-file"].as<string>());
}

TEST(ConfigFile, OverriddenByCommandLine) {
  po::variables_map vm;
  // Note that the path to a config file is relative to the directory this test is run in
  vector<string> argStrings = 
      {"./main", "--config-file", "../../src/test/run-configs/test-config.ini",
       "--input-file", "cmdline.json", "--output-file", "cmdline.csv",
       "--output-format", "CMD"};
  vector<char*> argChars;
  transform(argStrings.begin(), argStrings.end(), back_inserter(argChars), convert);

  EXPECT_TRUE(argparser::parse(argChars.size(), &argChars[0], vm));
  EXPECT_EQ("cmdline.json", vm["input-file"].as<string>());
  EXPECT_EQ("cmdline.csv", vm["output-file"].as<string>());
  EXPECT_EQ("CMD", vm["output-format"].as<string>());
}