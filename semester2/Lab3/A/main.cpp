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
  uniform_int_distribution<int> rand(-10, 10);
  uniform_real_distribution<double> drand(-100, 100);

  //------------------------- Work test ----------------------------------------

  cout << "--------------- Work test ---------------" << endl;
  cout << "100 sorting tests of random generated array (size = 1000):\n" << endl;

  int s = 0, q = 0, c = 0, m = 0, stds = 0;

  for (int j = 0; j < 100; ++j) {
    std::vector<double> a;

    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::selection(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) s++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::quicksort(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) q++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::merge(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) m++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::combined(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) c++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::std_sort(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) stds++;
  }


  cout << "Selection: " << setw(4) << s << "  tests passed" << endl;
  cout << "Quicksort: " << setw(4) << q << "  tests passed" << endl;
  cout << "    Merge: " << setw(4) << m << "  tests passed" << endl;
  cout << " Combined: " << setw(4) << c << "  tests passed" << endl;
  cout << "std::sort: " << setw(4) << stds << "  tests passed" << endl;



  cout << endl;

  //-------------------- Random array sorting demo ----------------------------------

  cout << fixed << setprecision(2);

  cout << "------- Random array sorting demo --------" << endl;

  std::vector<Point> a;

  for (int i = 0; i < 10; ++i) {
    a.emplace_back(Point(rand(re), rand(re), rand(re)));
  }

  cout << "A is random generated vector of points\n" << endl;
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


  return 0;
}