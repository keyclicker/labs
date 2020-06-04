#include "sorting.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
using namespace std;

struct Point {
  double x, y, z;

  Point() : x(0), y(0), z(0) {}
  Point(double x, double y, double z) : x(x), y(y), z(z) {}

  bool operator==(const Point &rhs) const {
    return x == rhs.x && y == rhs.y && z == rhs.z;
  }

  bool operator<(const Point &rhs) const {
    if (x < rhs.x)
      return true;
    else if (x == rhs.x) {
      if (y < rhs.y)
        return true;
      else if (y == rhs.y)
        if (z < rhs.z)
          return true;
    }
    return false;
  }

  bool operator>(const Point &rhs) const {
    if (x > rhs.x)
      return true;
    else if (x == rhs.x) {
      if (y > rhs.y)
        return true;
      else if (y == rhs.y)
        if (z > rhs.z)
          return true;
    }
    return false;
  }

  bool operator<=(const Point &rhs) const {
    return operator<(rhs) || operator==(rhs);
  }

  bool operator>=(const Point &rhs) const {
    return operator>(rhs) || operator==(rhs);
  }

  friend std::ostream &operator<<(std::ostream &out, const Point &p) {
    out << '(' << setw(7) << p.x << ", " <<
                  setw(7) << p.y << ", " <<
                  setw(7) << p.z << " )";
    return out;
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
  out << '{' << endl;
  for (auto i : v)
    out << i << ',' << endl;
  out << "};\n" << endl;
  return out;
}

int main() {
  random_device rd;
  default_random_engine re(rd());
  uniform_int_distribution<int> rand(0, 2000);

  cout << fixed << setprecision(2);

  std::vector<double> a;

  for (int i = 0; i < 10; ++i) {
    a.emplace_back(rand(re));
  }

  cout << "A is random generated vector of points" << endl;
  cout << "A = " << a;
  cout << endl;

  auto b = a;
  sorting::selection(b.begin(), b.end());
  cout << "B = A" << endl;
  cout << "sorting::selection(B);" << endl;
  cout << "B = " << b;
  cout << endl;

  b = a;
  sorting::quicksort(b.begin(), b.end());
  cout << "B = A" << endl;
  cout << "sorting::quicksort(B);" << endl;
  cout << "B = " << b;
  cout << endl;

  b = a;
  sorting::merge(b.begin(), b.end());
  cout << "B = A" << endl;
  cout << "sorting::merge(B);" << endl;
  cout << "B = " << b;
  cout << endl;

  b = a;
  sorting::combined(b.begin(), b.end());
  cout << "B = A" << endl;
  cout << "sorting::combined(B);" << endl;
  cout << "B = " << b;
  cout << endl;

  b = a;
  sorting::std_sort(b.begin(), b.end());
  cout << "B = A" << endl;
  cout << "sorting::std_sort(B);" << endl;
  cout << "B = " << b;
  cout << endl;


  int c = 0;
  for (int j = 0; j < 100; ++j) {
    std::vector<double> a;

    for (int i = 0; i < 100; ++i) {
      a.emplace_back(rand(re));
    }

    sorting::combined(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) c++;
  }
  cout << c;



  return 0;
}