#pragma once
#include "Config.hpp"

#include <iostream>
#include <algorithm>
#include <filesystem>
using namespace std;

template<typename T>
void genData(const string &filename, size_t n) {
  ofstream file(filename, ios::out | ios::binary);
  for (size_t i = 0; i < n; ++i) {
    T wr = rand() % 1000;
    file.write((char*)&wr, sizeof(T));
  }
}

template<typename T>
void printBinFile(const string &filename) {
  cout << "\nPrinting " + filename + ":" << endl;

  ifstream print(filename, ios::in | ios::binary);
  for (size_t i = 1; !print.eof(); ++i) {
    T wr;
    print.read((char*)&wr, sizeof(T));
    cout << wr << ' ';
    if (!(i % 20) && i) cout << endl;
  }
  cout << endl;
}

template<typename T>
void binSize(const string &filename) {
  cout << "\nSize of " + filename + ": ";

  ifstream print(filename, ios::in | ios::binary);

  size_t i;
  for (i = 0; !print.eof(); ++i) {
    T wr;
    print.read((char*)&wr, sizeof(T));
  }
  cout << i - 1 << endl;
}