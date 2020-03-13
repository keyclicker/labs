#include "Vector.hpp"
#include "Array.hpp"
#include "List.hpp"
#include <iostream>
using namespace std;

int main() {
  List<int> ls;

  ls.push_back(1);
  ls.push_back(2);
  ls.push_back(3);
  ls.push_back(4);

  ls.insert(1, 6);

  ls.clear();

  ls.insert(0, 9);

  cout << ls;
}