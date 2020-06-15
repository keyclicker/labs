#include "List.hpp"
#include "Vector.hpp"
#include "Tree.hpp"

#include <iostream>
using namespace std;

int main() {

  List<int> ls;
  Vector<int> vec;
  Tree<int> tree;


  cout << ls << '\n' << vec << '\n' << tree << endl;
}
