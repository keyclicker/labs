#include "Vector.hpp"
#include "Array.hpp"
#include <iostream>
using namespace std;

int main() {
  Vector<int> vc1 = {1, 2, 3, 4, 5};

  auto vc2 = vc1;

  Vector<int> vc3;

  vc3 = vc1;

  cout << vc1.size() << ' ' << vc2.size() << endl;

  cout << vc1 << endl;
  cout << vc2 << endl;
  cout << vc3 << endl;
}