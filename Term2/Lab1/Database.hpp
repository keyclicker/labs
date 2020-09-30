#pragma once

#include <list>
#include <string>
#include <fstream>
#include <iostream>

template<typename T>
class BaseDatabase {
public:
  void addFromTextFile(const std::string &path);
  void loadFromTextFile(const std::string &path);
  void saveToTextFile(const std::string &path) const;

  void addFromBinFile(const std::string &path);
  void loadFromBinFile(const std::string &path);
  void saveToBinFile(const std::string &path) const;

  void push(const T &val);
  std::list<T> &getData();
  const std::list<T> &getData() const;

  void print() const;
  size_t size() const;

private:
  std::list<T> dataList;
};

template<typename T>
class Database : BaseDatabase<T> {};


template<typename T>
void BaseDatabase<T>::push(const T &val) {
  dataList.push_back(val);
}

template<typename T>
std::list<T> &BaseDatabase<T>::getData() {
  return dataList;
}

template<typename T>
const std::list<T> &BaseDatabase<T>::getData() const {
  return dataList;
}

template<typename T>
size_t BaseDatabase<T>::size() const {
  return dataList.size();
}

template<typename T>
void BaseDatabase<T>::saveToTextFile(const std::string &path) const {
  std::ofstream out(path, std::ios::out);
  for (auto &a : dataList) {
    a.saveToTextFile(out);
    out << std::endl;
  }
}

template<typename T>
void BaseDatabase<T>::addFromTextFile(const std::string &path) {
  std::ifstream in(path, std::ios::in);
  while (!in.eof()) {
    T tmp;
    tmp.loadFromTextFile(in);
    dataList.emplace_back(tmp);
    in.get(), in.get();
  }
}

template<typename T>
void BaseDatabase<T>::saveToBinFile(const std::string &path) const {
  std::ofstream out(path, std::ios::out | std::ios::binary);

  size_t size = dataList.size();
  out.write((char*) &size, sizeof(size));
  for (auto &a : dataList)
    a.saveToBinFile(out);
}

template<typename T>
void BaseDatabase<T>::addFromBinFile(const std::string &path) {
  std::ifstream in(path, std::ios::in | std::ios::binary);

  size_t size;
  in.read((char*) &size, sizeof(size));
  for (size_t i = 0; i < size; ++i) {
    T tmp;
    tmp.loadFromBinFile(in);
    dataList.emplace_back(tmp);
  }
}

template<typename T>
void BaseDatabase<T>::print() const {
  for (size_t i = 0; i < dataList.size(); ++i) {
    std::cout << "ID: " << i << std::endl;
    std::next(dataList.begin(), i)->print();
  }
}

template<typename T>
void BaseDatabase<T>::loadFromTextFile(const std::string &path) {
  dataList.clear();
  addFromTextFile(path);
}

template<typename T>
void BaseDatabase<T>::loadFromBinFile(const std::string &path) {
  dataList.clear();
  addFromBinFile(path);
}


