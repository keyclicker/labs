#pragma once
#include "Config.hpp"

#include <iostream>
#include <algorithm>
#include <filesystem>
using namespace std;

void genData(const string &filename, int n) {
  ofstream file(filename, ios::out | ios::binary);
  for (int i = 0; i < n; ++i) {
    int wr = rand() % 100;
    file.write((char*)&wr, sizeof(int));
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