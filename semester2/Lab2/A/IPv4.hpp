#pragma once

#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>

class IPv4 {
private:
  uint8_t n[4];
public:
  IPv4(uint8_t n = 0) : n{n, n, n, n} {}
  IPv4(uint8_t n1, uint8_t n2, uint8_t n3, uint8_t n4) : n{n1, n2, n3, n4} {}

  auto &operator[](size_t index) {
    return n[index];
  }
  const auto &operator[](size_t index) const {
    return n[index];
  }

  friend std::ostream &operator<<(std::ostream &out, const IPv4 &ip) {
    out << (int)ip[0] << '.' << (int)ip[1]
    << '.' << (int)ip[2] << '.' << (int)ip[3];
    return out;
  }

  friend std::istream &operator>>(std::istream &in, IPv4 &ip) {
    std::string str;
    in >> str;
    std::replace(str.begin(), str.end(), '.', ' ');
    std::stringstream st(str);
    st >> (int&)ip[0] >> (int&)ip[1] >> (int&)ip[2] >> (int&)ip[3];
    return in;
  }
};