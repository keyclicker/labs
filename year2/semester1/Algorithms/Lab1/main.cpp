#include "ExternalSort.hpp"
#include "Utilities.hpp"

#include <vector>
using namespace std;

int main() {
  genData<int>("input.dat", FileSize);
  printBinFile<int>("input.dat");

  externalMergeSort<int>("input.dat");

//  for (int i = 0; i <= ChunkCount; ++i) {
//    printBinFile("chunk" + to_string(i) + ".dat");
//  }

  printBinFile<int>("res.dat");

  binSize<int>("input.dat");
  binSize<int>("res.dat");
  return 0;
}
