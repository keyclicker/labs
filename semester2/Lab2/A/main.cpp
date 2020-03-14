#include "Vector.hpp"
#include "Array.hpp"
#include "List.hpp"

#include <vector>
#include <iostream>
using namespace std;

int main() {
  List<int> ls = {1, 2, 3, 4};
  Vector<int> ls1 = {1, 2, 3, 4};
  Array<int, 4> ls2 = {1, 2, 3, 4};

  vector<int> v = {1, 2, 3, 4};
  auto l = ls;

  List<int> ll;
  ll = l;

  cout << ls2.at(2);
}