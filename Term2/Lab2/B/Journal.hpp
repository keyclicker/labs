#pragma once

#include <algorithm>
#include <chrono>
#include <string>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std::chrono;

class Message {
private:
  std::string message;
  system_clock::time_point time;

public:
  explicit Message(std::string msg = std::string()) :
          message(std::move(msg)), time(system_clock::now()) {}

  friend std::ostream& operator<<(std::ostream& out, const Message &val) {

    if (val.message.empty()) {
      out << "00:00:00 00.00.0000 : empty message";
    }
    else {
      using namespace std;
      time_t tt = system_clock::to_time_t(val.time);
      auto t = std::localtime(&tt);
      out  << setfill('0')
           << setw(2) << t->tm_hour << ':' << setw(2) << t->tm_min << ':'
           << setw(2) << t->tm_sec << ' ' << setw(2) << t->tm_mday << '.'
           << setw(2) << t->tm_mon << '.' << 1900 + t->tm_year << " : ";
      out << val.message;
      out << setfill(' ');
    }
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

  auto begin() {
    return std::begin(arr);
  }
  auto end() {
    return std::end(arr);
  }

  auto begin() const {
    return std::cbegin(arr);
  }
  auto end() const {
    return std::cend(arr);
  }

  size_t size() const {
    return size_;
  }

  void push(const T &val) {
    arr[index] = val;
    if (++index >= size_) index = 0;
  }

  T &operator[](const T &indx) {
    return arr[indx];
  }
  const T &operator[](const T &indx) const {
    return arr[indx];
  }

  void printLast(size_t k) const {
    if (k > size_) k = size_;
    for (int i = size_ - k; i < size_; ++i) {
      std::cout << '[' << i << "] " << arr[i] << (i == index ? "  <-" : "") << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Journal &val) {
    out << "Size: " << val.size_ << "  Pos: " << val.index << std::endl;
    for (int i = 0; i < val.size_; ++i) {
      out  << '[' << i << "] " << val.arr[i] << (i == val.index ? "  <-" : "") << std::endl;
    }
    return out;
  }
};