#include "src/List.hpp"
#include "src/Vector.hpp"
#include "src/Tree.hpp"
#include "src/AVL.hpp"

#include <set>
#include <random>
#include <iostream>
#include "string"
using namespace std;

template<typename T>
auto rand(T a, T b) {
  random_device rd;
  default_random_engine re(rd());
  uniform_int_distribution<T> drand(a, b);
  return drand(re);
}

int main() {

  List<string> ls;
  Vector<string> vec;
  Tree<string> tree;
  AvlTree<string> avl;

  for (int i = 0; i < 10; ++i) {
    string s;
    for (int j = 0; j < rand(2, 4); ++j) {
      s.push_back(rand('a','z'));
    }

    ls.insert(s);
    vec.insert(s);
    tree.insert(s);
    avl.insert(s);
  }

  cout << "Inserting 10 random values in containers:" << endl;

  cout
  << "List:    " << ls << " size = " << ls.size() << '\n'
  << "Vector:  " << vec << " size = " << vec.size() << '\n'
  << "BSTree:  " << tree  << " size = " << tree.size() << '\n'
  << "AVLTree: " << avl << " size = " << avl.size() << endl;

  auto fnd = vec[3];
  cout << "\nFind \"" << fnd << "\":"<< endl;

  cout << "List:    ";
  for (auto i = ls.begin(); i != ls.end(); ++i) {
    cout << left << setw(10) << (ls.find(fnd) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "Vector:  ";
  for (auto i = vec.begin(); i != vec.end(); ++i) {
    cout << left << setw(10) << (vec.find(fnd) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "BSTree:  ";
  for (auto i = tree.begin(); i != tree.end(); ++i) {
    cout << left << setw(10) << (tree.find(fnd) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "AVLTree: ";
  for (auto i = avl.begin(); i != avl.end(); ++i) {
    cout << left << setw(10) << (avl.find(fnd) == i ? "-> " : "") + *i;
  } cout << endl;

  auto fnd1 = vec[2], fnd2 = vec[4];
  cout << "\nFind \"" << fnd1 << "\"-\"" << fnd2 << "\":"<< endl;

  cout << "List:    ";
  for (auto i = ls.begin(); i != ls.end(); ++i) {
    cout << left << setw(10) << (ls.find(fnd1, fnd2) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "Vector:  ";
  for (auto i = vec.begin(); i != vec.end(); ++i) {
    cout << left << setw(10) << (vec.find(fnd1, fnd2) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "BSTree:  ";
  for (auto i = tree.begin(); i != tree.end(); ++i) {
    cout << left << setw(10) << (tree.find(fnd1, fnd2) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "AVLTree: ";
  for (auto i = avl.begin(); i != avl.end(); ++i) {
    cout << left << setw(10) << (avl.find(fnd1, fnd2) == i ? "-> " : "") + *i;
  } cout << endl;

  auto rm1 = vec[1], rm2 = vec[5];
  cout << "\nRemoving \"" << rm1 << "\" and \"" << rm2 << "\":"<< endl;

  ls.remove(rm1);
  ls.remove(rm2);
  vec.remove(rm1);
  vec.remove(rm2);
  tree.remove(rm1);
  tree.remove(rm2);
  avl.remove(rm1);
  avl.remove(rm2);

  cout
  << "List:    " << ls << " size = " << ls.size() << '\n'
  << "Vector:  " << vec << " size = " << vec.size() << '\n'
  << "BSTree:  " << tree  << " size = " << tree.size() << '\n'
  << "AVLTree: " << avl << " size = " << avl.size() << endl;

  cout << "\nFor-range append \'++\':"<< endl;

  for (auto &a : ls) a.append("++");
  for (auto &a : vec) a.append("++");
  for (auto &a : tree) a.append("++");
  for (auto &a : avl) {
    a.append("++");
  }


  cout
  << "List:    " << ls << " size = " << ls.size() << '\n'
  << "Vector:  " << vec << " size = " << vec.size() << '\n'
  << "BSTree:  " << tree  << " size = " << tree.size() << '\n'
  << "AVLTree: " << avl << " size = " << avl.size() << endl;


}
