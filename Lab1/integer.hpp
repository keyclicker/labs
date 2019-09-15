#pragma once

#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>

using Byte = char;

class Integer
{
private:
  bool negetive = false;
  std::vector<Byte> num;

  static Integer sum(const Integer &a, const Integer &b);
  static Integer sub(const Integer &a, const Integer &b);

public:
  Integer();
  Integer(const Integer &val);
  Integer &operator=(const Integer &val);

  Integer(long long val);
  Integer(const std::string &val);

  operator std::string() const;
  operator int() const;

  Integer operator+(const Integer &val) const;
  Integer operator-(const Integer &val) const;
  Integer operator*(const Integer &val) const;
  Integer operator/(long long val) const;

  bool operator>(const Integer &val) const;
  bool operator<(const Integer &val) const;
  bool operator>=(const Integer &val) const;
  bool operator<=(const Integer &val) const;
  bool operator==(const Integer &val) const;

  friend std::istream &operator>>(std::istream &in, Integer &val);
  friend std::ostream &operator<<(std::ostream &out, Integer val);
};