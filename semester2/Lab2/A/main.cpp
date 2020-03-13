#include "Vector.hpp"
#include "Array.hpp"
#include "List.hpp"
#include <iostream>
using namespace std;

int main() {
  List<int> ls = {1, 2, 3, 4};

  auto l = ls;

  List<int> ll;
  ll = l;

  cout << ll;
}