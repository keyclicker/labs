#include "src/List.hpp"
#include "src/Vector.hpp"
#include "src/Tree.hpp"
#include "src/AVL.hpp"

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

List<string> ls;
Vector<string> vec;
Tree<string> tree;
AvlTree<string> avl;

void help() {
  constexpr int w = 25;

  cout << setw(w) << left <<
       "rand <count>" << "Insert <count> rand values" << endl;
  cout << setw(w) << left <<
       "insert <value>" << "Insert value in containers" << endl;
  cout << setw(w) << left <<
       "remove <value>" << "Remove value from containers" << endl;
  cout << setw(w) << left <<
       "find <value>" << "Find value in containers" << endl;
  cout << setw(w) << left <<
       "findr <v1> <v2>" << "Find value in range v1 - v2" << endl;
  cout << setw(w) << left <<
       "print" << "Print containers" << endl;
  cout << setw(w) << left <<
       "clear" << "Clear containers" << endl;
  cout << setw(w) << left <<
       "help" << "To get help" << endl;
}

void clear() {
  ls.clear();
  vec.clear();
  tree.clear();
  avl.clear();
}

void print() {
  cout  << "List:    " << ls << " size = " << ls.size() << '\n'
        << "Vector:  " << vec << " size = " << vec.size() << '\n'
        << "BSTree:  " << tree  << " size = " << tree.size() << '\n'
        << "AVLTree: " << avl << " size = " << avl.size() << endl;
}

void find() {
  string value;
  cin >> value;

  cout << "List:    ";
  for (auto i = ls.begin(); i != ls.end(); ++i) {
    cout << left << setw(10) << (ls.find(value) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "Vector:  ";
  for (auto i = vec.begin(); i != vec.end(); ++i) {
    cout << left << setw(10) << (vec.find(value) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "BSTree:  ";
  for (auto i = tree.begin(); i != tree.end(); ++i) {
    cout << left << setw(10) << (tree.find(value) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "AVLTree: ";
  for (auto i = avl.begin(); i != avl.end(); ++i) {
    cout << left << setw(10) << (avl.find(value) == i ? "-> " : "") + *i;
  } cout << endl;
}

void findr() {
  string v1, v2;
  cin >> v1 >> v2;

  cout << "List:    ";
  for (auto i = ls.begin(); i != ls.end(); ++i) {
    cout << left << setw(10) << (ls.find(v1, v2) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "Vector:  ";
  for (auto i = vec.begin(); i != vec.end(); ++i) {
    cout << left << setw(10) << (vec.find(v1, v2) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "BSTree:  ";
  for (auto i = tree.begin(); i != tree.end(); ++i) {
    cout << left << setw(10) << (tree.find(v1, v2) == i ? "-> " : "") + *i;
  } cout << endl;
  cout << "AVLTree: ";
  for (auto i = avl.begin(); i != avl.end(); ++i) {
    cout << left << setw(10) << (avl.find(v1, v2) == i ? "-> " : "") + *i;
  } cout << endl;
}

void insert() {
  string value;
  cin >> value;

  ls.insert(value);
  vec.insert(value);
  tree.insert(value);
  avl.insert(value);
}

void random_() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    for (int j = 0; j < rand(2, 4); ++j) {
      s.push_back(rand('a','z'));
    }

    ls.insert(s);
    vec.insert(s);
    tree.insert(s);
    avl.insert(s);
  }
}

void remove() {
  string value;
  cin >> value;

  ls.remove(value);
  vec.remove(value);
  tree.remove(value);
  avl.remove(value);
}

int main() {
  cout << "Type \"help\" to get help" << endl;

  string cmd;

  while (cmd != "exit") {
    cin >> cmd;

    if (cmd == "clear") clear();
    else if (cmd == "rand") random_();
    else if (cmd == "print") print();
    else if (cmd == "find") find();
    else if (cmd == "findr") findr();
    else if (cmd == "insert") insert();
    else if (cmd == "remove") remove();
    else if (cmd == "help") help();
  }
}