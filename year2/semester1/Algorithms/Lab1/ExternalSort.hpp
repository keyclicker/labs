#pragma once
#include "Config.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

using namespace std;

template<typename T>
void splitAndSort(const string &filename) {
  ifstream file(filename, ios::in | ios::binary);

  for (size_t i = 0; !file.eof(); ++i) {
    vector<T> chunk(ChunkSize);
    file.read((char*)chunk.data(), sizeof(T) * ChunkSize);
    sort(chunk.begin(), chunk.end());

    ofstream chunkf("chunk" + to_string(i) + ".dat", ios::out | ios::binary);
    chunkf.write((char*)chunk.data(), sizeof(T) * ChunkSize);
  }
  file.close();

}

template<typename T>
void externalMergeSort(const string &filename) {
  splitAndSort<T>(filename);

  constexpr auto memChunckSize = ChunkSize / (ChunkCount + 1);

  //Chunks in memory
  vector<vector<T>> vec(ChunkCount, vector<T>(memChunckSize));
  //Chunk indices
  vector<std::size_t> indices(ChunkCount, 0);

  //Opening chunk files
  vector<ifstream> files(ChunkCount);
  for (size_t i = 0; i < ChunkCount; ++i) {
    files[i].open("chunk" + to_string(i) + ".dat", ios::in | ios::binary);
    files[i].read((char*)vec[i].data(), sizeof(T) * memChunckSize);
  }

  //Result file
  ofstream res("res.dat", ios::out | ios::binary);

  for (size_t i = 0;; ++i) {
    size_t min = 0; //index of chunk with minimal element
    while (indices[min] >= ChunkSize) min++; //todo test
    if (min >= ChunkCount) break; //breaking if every index greater than ChunkSize

    //Searching for min
    for (size_t j = 0; j < ChunkCount; ++j) {
      if (vec[min][indices[min] % memChunckSize] >
                vec[j][indices[j] % memChunckSize] &&
                               indices[j] < ChunkSize) {
        min = j;
      }
    }

    if (indices[min] < ChunkSize) {
      //DEBUG
      static T prev = 0;
      if (vec[min][indices[min] % memChunckSize] < prev) {
        cout << "Not sorted!!!" << endl;
      }

      prev = vec[min][indices[min] % memChunckSize];
      //DEBUG-end

      //cout << vec[min][indices[min] % memChunckSize] << '\n'; //todo remove debug
      res.write((char*)&vec[min][indices[min] % memChunckSize], sizeof(T)); //todo remove debug

      ++indices[min];

      if (indices[min] % memChunckSize == 0 && indices[min]) {
        files[min].read((char*)vec[min].data(), sizeof(T) * memChunckSize);
      }
    }
  }


  //Deleting chunk files
  for (size_t i = 0; i < ChunkCount; ++i) {
    std::filesystem::remove("chunk" + to_string(i) + ".dat");
  }
}