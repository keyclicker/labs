#pragma once

#include <vector>
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
void sortFile(const string &input, const string &output, size_t n) {
  vector<T> vec(n);
  ifstream in(input, ios::in | ios::binary);
  in.read((char*)vec.data(), sizeof(T)*n);

  sort(vec.begin(), vec.end());

  ofstream out(output, ios::out | ios::binary);
  out.write((char*)vec.data(), sizeof(T)*n);
}

template<typename T>
bool compFiles(const string &aPath, const string &bPath, size_t n) {
  vector<T> aVec(n), bVec(n);
  ifstream
    aFile(aPath, ios::in | ios::binary),
    bFile(bPath, ios::in | ios::binary);

  aFile.read((char*)aVec.data(), sizeof(T)*n);
  bFile.read((char*)bVec.data(), sizeof(T)*n);

  for (int i = 0; i < n; ++i) {
    if (aVec[i] != bVec[i])
      return false;
  }
  return true;
}

template<typename T>
void printBinFile(const string &filename) {
  cout << "\nPrinting " + filename + ":" << endl;

  ifstream print(filename, ios::in | ios::binary);
  for (size_t i = 0; !print.eof(); ++i) {
    T wr;
    print.read((char*)&wr, sizeof(T));
    cout << wr << ' ';
    if (!(i % 20) && i) cout << endl;
  }
  cout << endl;
}

template<typename T>
auto binSize(const string &filename) {
  ifstream print(filename, ios::in | ios::binary);
  size_t i;
  for (i = 0; !print.eof(); ++i) {
    T wr;
    print.read((char*)&wr, sizeof(T));
  }
  return i - 1;
}