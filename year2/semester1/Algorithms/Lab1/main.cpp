#include "ExternalSort.hpp"
#include "Utilities.hpp"

#include <vector>
using namespace std;


constexpr std::size_t
        FileSize = 1000,
        ChunkSize = 100;

int main() {
  genData<int>("input.dat", FileSize);
  printBinFile<int>("input.dat");

  externalMergeSort<int>("input.dat", "res.dat", FileSize, ChunkSize);

//  for (int i = 0; i <= ChunkCount; ++i) {
//    printBinFile("chunk" + to_string(i) + ".dat");
//  }

  printBinFile<int>("res.dat");

  cout << "\nSize of input.dat: " << binSize<int>("input.dat") << endl;
  cout << "\nSize of res.dat: " << binSize<int>("res.dat") << endl;
  return 0;
}
