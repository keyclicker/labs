#pragma once

#include <algorithm>
#include <chrono>
#include <string>
#include <utility>
#include <iostream>

using namespace std::chrono;

class Message {
private:
  std::string message;
  system_clock::time_point time;

public:
  explicit Message(std::string msg = std::string()) :
          message(std::move(msg)), time(system_clock::now()) {}

  friend std::ostream& operator<<(std::ostream& out, const Message &val) {
    time_t tt = system_clock::to_time_t(val.time);
    auto t = std::localtime(&tt);
    out  << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ' '
         << t->tm_mday << '.' << t->tm_mon << '.' << 1900 + t->tm_year << " : ";
    out << val.message;
    return out;
  }
};

template<typename T>
class Journal {
private:
  T *arr;
  size_t index ;
  size_t size_;

public:
  explicit Journal(size_t size = 0) : size_(size), arr(new T[size]), index(0) {}

  Journal (const Journal &rhs) :
  size_(rhs.size_), index(rhs.index), arr(new T[rhs.size_]) {
    for (int i = 0; i < size_; ++i) {
      arr[i] = rhs.arr[i];
    }
  }
  Journal &operator=(const Journal &rhs) {
    size_ = rhs.size_, index = rhs.index, arr = new T[rhs.size_];
    for (int i = 0; i < size_; ++i) {
      arr[i] = rhs.arr[i];
    }
  }

  Journal(Journal &&rhs) :
        size_(rhs.size_), index(rhs.index), arr(rhs.arr) {
    rhs.arr = nullptr;
    rhs.size_ = 0;
    rhs.index = 0;
    return *this;
  }
  Journal &operator=(Journal &&rhs) {
    size_ = rhs.size_, index = rhs.index, arr = rhs.arr;
    rhs.arr = nullptr;
    rhs.size_ = 0;
    rhs.index = 0;
    return *this;
  }

  ~Journal() {
    delete[] arr;
  }

  T *begin() {
    return std::begin(arr);
  }
  T *end() {
    return std::end(arr);
  }

  size_t size() {
    return size_;
  }

  void push(const T &val) {
    arr[index] = val;
    if (++index >= size_) index = 0;
  }

  T &operator[](const T &indx) {
    return arr[indx];
  }

  friend std::ostream& operator<<(std::ostream& out, const Journal &val) {
    out << "Size: " << val.size_ << "  Pos: " << val.index << std::endl;
    for (int i = 0; i < val.size_; ++i) {
      out << val.arr[i] << (i == val.index ? "  <-" : "") << std::endl;
    }
    return out;
  }
};