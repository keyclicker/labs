#include "Manager.hpp"
#include "Functions.hpp"
#include "Config.hpp"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    runManager<Config::ValueType>(argv[0]);
  }
  else if (strcmp(argv[1], "-f") == 0) {
    functionF<Config::ValueType>();
  }
  else if (strcmp(argv[1], "-g") == 0) {
    functionG<Config::ValueType>();
  }

  return 0;
}