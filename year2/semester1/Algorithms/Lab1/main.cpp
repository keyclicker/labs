#include "ExternalSort.hpp"
#include "Utilities.hpp"

#include <vector>
using namespace std;

int main() {
  genData("input.dat", FileSize);
  printBinFile("input.dat");

  externalMergeSort("input.dat");

//  for (int i = 0; i <= ChunkCount; ++i) {
//    printBinFile("chunk" + to_string(i) + ".dat");
//  }

  printBinFile("res.dat");

  binSize("input.dat");
  binSize("res.dat");
  return 0;
}
