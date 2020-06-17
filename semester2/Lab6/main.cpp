#include "List.hpp"
#include "Vector.hpp"
#include "Tree.hpp"

#include <random>
#include <iostream>
using namespace std;

template<typename T>
auto rand(T a, T b) {
  random_device rd;
  default_random_engine re(rd());
  uniform_int_distribution<T> drand(a, b);
  return drand(re);
}

int main() {

  List<int> ls;
  Vector<int> vec;
  Tree<int> tree;

  for (int i = 0; i < 10; ++i) {
    auto r = rand(0, 10);
    ls.insert(r);
    vec.insert(r);
    tree.insert(r);
  }

//  ls.remove(6);
//  vec.remove(6);

  cout << ls << '\n' << vec << '\n' << tree << endl;

  cout << *vec.find(4, 6) << endl;


  cout << tree.front() << ' ' << tree.back() << endl;

  for (auto a = tree.begin(); a != tree.end(); ++a)
    cout << *a << ' ';

  cout << endl;

  cout << *tree.find(30, 35) << endl;

  cout << tree << endl;

  tree.remove(6);
  tree.remove(6);
  cout << tree << endl;

  cout << tree << endl;

}
