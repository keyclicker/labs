#pragma once

#include <iostream>
#include <list>

class Point {
public:
    double x, y;
    Point(): x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
};

ostream& operator<<(ostream& os, const Point& dt) {
    os << "(" << dt.x << ", " << dt.y << ")";
    return os;
}

template <typename T = size_t>
class Range {
public:
  T min, max;
  Range(): min(0), max(0) {}
  Range(T min, T max) : min(min), max(max) {}
  
  bool operator==(const Range& other) const {
    return min == other.min && max == other.max;
  }
};

template <typename T>
ostream& operator<<(ostream& os, const Range<T>& dt) {
    os << "[" << dt.min << ", " << dt.max << ")";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const list<T>& dt) {
    os << "[";
    for (auto it = dt.begin(); it != dt.end(); ++it) {
        if (it != dt.begin()) os << ", ";
        os << *it;
    }
    os << "]";
    return os;
}