#include "Vector.hpp"
#include "Array.hpp"
#include <iostream>
using namespace std;

int main() {
  Array<int, 5> vc = {1, 2, 3, 4, 5};

  cout << vc.size() << endl;

  vc.back() = 0;

  for (auto a : vc) {
    cout << a << ' ';
  }
}