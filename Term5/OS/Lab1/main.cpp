#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <memory>

#include <boost/process.hpp>

namespace bp = boost::process;
namespace fs = boost::filesystem;

#include "Server.hpp"

int f() {


  std::cout << "hello from f" << std::endl;


  return 0;
}

int g() {
  std::cout << "hello from g" << std::endl;
  return 0;
}

int manager(const char *path) {

  bp::spawn(path, "-f");
  bp::spawn(path, "-g");

  std::cout << "Input X" << std::endl;

  int x;
  std::cin >> x;

  return 0;
}


int main(int argc, char *argv[]) {
  if (argc == 1) {
    return manager(argv[0]);
  }
  else if (strcmp(argv[1], "-f") == 0) {
    return f();
  }
  else if (strcmp(argv[1], "-g") == 0) {
    return g();
  }

  return 0;
}