#include "ExternalSort.hpp"
#include "Utilities.hpp"

#include <vector>
using namespace std;


constexpr std::size_t
        FileSize = 200,
        ChunkSize = 1000;

int main() {
  genData<int>("input.dat", FileSize);
  printBinFile<int>("input.dat");

  externalMergeSort<int>("input.dat", "res.dat", FileSize, ChunkSize);
  sortFile<int>("input.dat", "memsort.dat", FileSize);

//  for (int i = 0; i <= ChunkCount; ++i) {
//    printBinFile("chunk" + to_string(i) + ".dat");
//  }

  printBinFile<int>("res.dat");
  printBinFile<int>("memsort.dat");

  cout << '\n' << compFiles<int>("res.dat", "memsort.dat", FileSize) << endl;

  cout << "\nSize of input.dat: " << binSize<int>("input.dat") << endl;
  cout << "\nSize of res.dat: " << binSize<int>("res.dat") << endl;
  return 0;
}
