#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include "proto/message.pb.h"

int main() {
  message::Message m;
  std::vector<std::string> temp = {"test1", "test2"};

  std::cout << "Hello" << std::endl;

  boost::filesystem::path full_path(boost::filesystem::current_path());
  std::cout << "Current path is : " << full_path << std::endl;

  return 0;
}
