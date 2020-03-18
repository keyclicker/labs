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

template<typename T, size_t S>
class Journal {
private:
  T arr[S];
  size_t index = 0;

public:
  auto begin() {
    return std::begin(arr);
  }
  auto end() {
    return std::end(arr);
  }

  void push(const T &val) {
    arr[index] = val;
    if (++index >= S) index = 0;
  }

  T &operator[](const T &indx) {
    return arr[indx];
  }

  friend std::ostream& operator<<(std::ostream& out, const Journal &val) {
    out << "Size: " << S << "  Pos: " << val.index << std::endl;
    for (int i = 0; i < S; ++i) {
      out << val.arr[i] << (i == val.index ? "  <-" : "") << std::endl;
    }
    return out;
  }
};