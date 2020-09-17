#include <iostream>
#include <algorithm>
#include <filesystem>
#include <memory>
#include <fstream>
#include <vector>
using namespace std;

constexpr std::size_t
FileSize = 800,
ChunkSize = 100,
ChunkCount = FileSize / ChunkSize; ////todo

void genData(const string &filename, int n) {
  ofstream file(filename, ios::out | ios::binary);
  for (int i = 0; i < n; ++i) {
    int wr = rand() % 100;
    file.write((char*)&wr, sizeof(int));
  }
}

void externalMergeSort(const string &filename) {
  ifstream file("input.dat", ios::in | ios::binary);

  for (int i = 0; !file.eof(); ++i) {
    vector<int> chunk(ChunkSize);
    file.read((char*)chunk.data(), sizeof(int) * ChunkSize);
    sort(chunk.begin(), chunk.end());

    ofstream chunkf("chunk" + to_string(i) + ".dat", ios::out | ios::binary);
    chunkf.write((char*)chunk.data(), sizeof(int) * ChunkSize);
  }
  file.close();

  auto s = ChunkSize / (ChunkCount + 1);
  vector<vector<int>> vec(ChunkCount, vector<int>(s));
  vector<ifstream> files(ChunkCount);
  files.reserve(ChunkCount);

  for (int i = 0; i < ChunkCount; ++i) {
    files[i].open("chunk" + to_string(i) + ".dat", ios::in | ios::binary);
    files[i].read((char*)vec[i].data(), sizeof(int) * s);
  }

  ofstream res("res.dat", ios::out | ios::binary);
  vector<std::size_t> indices(ChunkCount, 0);
  for (int i = 0; i < FileSize; ++i) {
    int min = 0;
    for (int j = 0; j < ChunkCount; ++j) {
      if (vec[min][indices[min]] > vec[j][indices[j]])
        min = j;
    }

    static int prev = 0;
    if (vec[min][indices[min]] < prev) {
      int io = 0;
    }

    prev = vec[min][indices[min]];

    cout << vec[min][indices[min]] << '\n';
    res.write((char*)&vec[min][indices[min]], sizeof(int)); //todo debug

    ++indices[min];
    if (indices[min] >= s) {
      indices[min] = 0;
      files[min].read((char*)vec[min].data(), sizeof(int) * s);
    }
  }


  for (int i = 0; i < ChunkCount; ++i) {
    ifstream in("chunk" + to_string(i) + ".dat", ios::in | ios::binary);
    in.read((char*)vec[i].data(), sizeof(int) * s);
    files.emplace_back(std::move(in));
  }

  for (int i = 0; i < ChunkCount; ++i) {
    std::filesystem::remove("chunk" + to_string(i) + ".dat");
  }
}

void printBinFile(const string &filename) {
  cout << "\nPrinting " + filename + ":" << endl;

  ifstream print(filename, ios::in | ios::binary);
  for (int i = 1; !print.eof(); ++i) {
    int wr;
    print.read((char*)&wr, sizeof(int));
    cout << wr << ' ';
    if (!(i % 20) && i) cout << endl;
  }
  cout << endl;
}

void binSize(const string &filename) {
  cout << "\nSize of " + filename + ": ";

  ifstream print(filename, ios::in | ios::binary);

  int i;
  for (i = 1; !print.eof(); ++i) {
    int wr;
    print.read((char*)&wr, sizeof(int));
  }
  cout << i << endl;
}


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
