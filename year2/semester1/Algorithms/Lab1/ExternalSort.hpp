#pragma once
#include "Config.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

using namespace std;

void splitAndSort(const string &filename) {
  ifstream file(filename, ios::in | ios::binary);

  for (int i = 0; !file.eof(); ++i) {
    vector<int> chunk(ChunkSize);
    file.read((char*)chunk.data(), sizeof(int) * ChunkSize);
    sort(chunk.begin(), chunk.end());

    ofstream chunkf("chunk" + to_string(i) + ".dat", ios::out | ios::binary);
    chunkf.write((char*)chunk.data(), sizeof(int) * ChunkSize);
  }
  file.close();

}

void externalMergeSort(const string &filename) {
  splitAndSort(filename);

  constexpr auto memChunckSize = ChunkSize / (ChunkCount + 1);

  //Chunks in memory
  vector<vector<int>> vec(ChunkCount, vector<int>(memChunckSize));
  //Chunk indices
  vector<std::size_t> indices(ChunkCount, 0);

  //Opening chunk files
  vector<ifstream> files(ChunkCount);
  for (int i = 0; i < ChunkCount; ++i) {
    files[i].open("chunk" + to_string(i) + ".dat", ios::in | ios::binary);
    files[i].read((char*)vec[i].data(), sizeof(int) * memChunckSize);
  }

  //Result file
  ofstream res("res.dat", ios::out | ios::binary);

  for (int i = 0;; ++i) {
    size_t min = 0; //index of chunk with minimal element
    while (indices[min] >= ChunkSize) min++; //todo test
    if (min >= ChunkCount) break; //breaking if every index greater than ChunkSize

    //Searching for min
    for (int j = 0; j < ChunkCount; ++j) {
      if (vec[min][indices[min] % memChunckSize] >
                vec[j][indices[j] % memChunckSize] &&
                               indices[j] < ChunkSize) {
        min = j;
      }
    }

    if (indices[min] < ChunkSize) {
      //DEBUG
      static int prev = 0;
      if (vec[min][indices[min] % memChunckSize] < prev) {
        int io = 0;
      }

      prev = vec[min][indices[min] % memChunckSize];
      //DEBUG-end

      //cout << vec[min][indices[min] % memChunckSize] << '\n'; //todo remove debug
      res.write((char*)&vec[min][indices[min] % memChunckSize], sizeof(int)); //todo remove debug

      if (indices[min] % memChunckSize == 0) {
        files[min].read((char*)vec[min].data(), sizeof(int) * memChunckSize);
      }
      ++indices[min];
    }
    else
      int lel = 5;


  }


  //Deleting chunk files
  for (int i = 0; i < ChunkCount; ++i) {
    //std::filesystem::remove("chunk" + to_string(i) + ".dat");
  }
}