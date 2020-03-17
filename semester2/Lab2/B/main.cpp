#include "Set.hpp"
#include <iostream>
using namespace std;

int main() {

  Set<int> a = {2, 3, 5, 7, 7, 6};
  Set<int> b = {6, 7, 8};

  cout << a-b;
}