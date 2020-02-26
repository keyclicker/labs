#pragma once

#include <list>
#include <string>
#include <fstream>
#include "Message.hpp"

template<typename T = Message>
class Database {
private:
  std::list<T> dataList; //todo Message to T

public:
  void addFromTextFile(const std::string &path);
  void loadFromTextFile(const std::string &path);
  void saveToTextFile(const std::string &path) const;

  void addFromBinFile(const std::string &path);
  void loadFromBinFile(const std::string &path);
  void saveToBinFile(const std::string &path) const;

  void print() const;
  size_t size() const;
};

template<typename T>
size_t Database<T>::size() const {
  return dataList.size();
}

template<typename T>
void Database<T>::saveToTextFile(const std::string &path) const {
  std::ofstream out(path, std::ios::out);
  for (auto &a : dataList)
    a.saveToTextFile(out);
}

template<typename T>
void Database<T>::addFromTextFile(const std::string &path) {
  std::ifstream in(path, std::ios::in);
  while (!in.eof()) {
    T tmp;
    tmp.loadFromTextFile(in);
    dataList.push_back(tmp);
  }
}

template<typename T>
void Database<T>::saveToBinFile(const std::string &path) const {
  std::ofstream out(path, std::ios::out | std::ios::binary);

  size_t size = dataList.size();
  out.write((char*) &size, sizeof(size));
  for (auto &a : dataList)
    a.saveToBinFile(out);
}

template<typename T>
void Database<T>::addFromBinFile(const std::string &path) {
  std::ifstream in(path, std::ios::in | std::ios::binary);

  size_t size;
  in.read((char*) &size, sizeof(size));
  for (size_t i = 0; i < size; ++i) {
    T tmp;
    tmp.loadFromBinFile(in);
    dataList.push_back(tmp);
  }
}

template<typename T>
void Database<T>::print() const {
  for (auto &a : dataList)
    a.print();
}

template<typename T>
void Database<T>::loadFromTextFile(const std::string &path) {
  dataList.clear();
  addFromTextFile(path);
}

template<typename T>
void Database<T>::loadFromBinFile(const std::string &path) {
  dataList.clear();
  addFromBinFile(path);
}

