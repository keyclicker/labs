#include "Matrix.hpp"

#include <iostream>
#include <vector>
using namespace std;


int main() {
  Matrix<int> a({
    {-1, 4},
    {2, 3},
  });

  Matrix<int> b({
    {9, -3},
    {6, 1},
  });

  cout << a << endl;
  cout << b << endl;
  cout << a*b << endl;
  cout << a.strassenMultiply(b) << endl;


  constexpr std::size_t size = 18;
  Matrix<int> c(size, size), d(size, size);

  srand(time(NULL));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      c.set(i, j, rand() % 20 - 10);
      d.set(i, j, rand() % 20 - 10);
    }
  }

  cout << ((c*d) == c.strassenMultiply(d)) << endl;

  cout << c << endl;
  cout << d << endl;
  cout << c*d << endl;
  cout << c.strassenMultiply(d) << endl;
}