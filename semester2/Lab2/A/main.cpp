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

//  ls.push_front(1);
//  ls.push_front(2);
//  ls.push_front(3);
//  ls.push_front(4);

  auto a = ls.begin();;
  cout << *((a+1)-1) << endl;

  for (auto a : ls) {
    cout << a << ' ';
  }
}