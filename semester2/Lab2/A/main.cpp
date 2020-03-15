#include "Vector.hpp"
#include "Array.hpp"
#include "List.hpp"
#include "Container.hpp"

#include <map>
#include <list>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

map<string, shared_ptr<DynamicContainer<int>>> cons;

void create() {
  string name, type;
  cin >> name >> type;

  if (type == "-vector") {
    cons[name] =  shared_ptr<DynamicContainer<int>>(new Vector<int>());
  }
  else if (type == "-list") {
    cons[name] =  shared_ptr<DynamicContainer<int>>(new List<int>());
  }
}

void append() {
  string name, values;
  cin >> name;

  getline(cin, values);
  stringstream st;
  st << values;

  while (!st.eof()) {
    int value;
    st >> value;
    cons[name]->push_back(value);
  }
}

void insert() {
  int index;
  string name, values;
  cin >> name >> index;

  getline(cin, values);
  stringstream st;
  st << values;

  while (!st.eof()) {
    int value;
    st >> value;
    cons[name]->insert(index++, value);
  }
}

void remove () {
  string name;
  int index;
  cin >> name >> index;
  cons[name]->erase(index);
}

void get() {
  string name;
  int index;
  cin >> name >> index;
  cout << cons[name]->at(index) << endl;
}

void set() {
  string name;
  int index, value;
  cin >> name >> index >> value;
  cons[name]->at(index) = value;
}

void length() {
  string name;
  int index;
  cin >> name;
  cout << cons[name]->size() << endl;
}

void print() {
  string name;
  int index;
  cin >> name;
  cons[name]->print();
}

void ls() {
  for (auto a : cons) {
    cout << a.first << " : " << a.second->size() << " elements" << endl;
  }
}

void del() {
  string name;
  cin >> name;
  cons.erase(name);
}

void help() {
  constexpr int w = 35;

  cout << setw(w) << left <<
  "create <name> -<type>" << "Create list, <type> = {-list, -vector}" << endl;
  cout << setw(w) << left <<
  "del <name>" << "Delete list" << endl;
  cout << setw(w) << left <<
  "len <name>" << "Get size of list" << endl;
  cout << setw(w) << left <<
  "print <name>" << "Print list" << endl;
  cout << setw(w) << left <<
  "ls" << "List lists" << endl;
  cout << setw(w) << left <<
  "append <name> <values>" << "Append values" << endl;
  cout << setw(w) << left <<
  "insert <name> <index> <values>" << "Insert values" << endl;
  cout << setw(w) << left <<
  "remove <name> <index>" << "Remove element by index" << endl;
  cout << setw(w) << left <<
  "get <name> <index>" << "Get element by index" << endl;
  cout << setw(w) << left <<
  "set <name> <index> <value>" << "Set element by index" << endl;
  cout << setw(w) << left <<
  "help" << "Run help" << endl;
  cout << setw(w) << left <<
  "demo" << "Run demo" << endl;
}

void demo() {
  cout << "Creating Array<int, 5> A initialized with {1, 2, 3, 4, 5}" << endl;
  Array<int, 5> A = {1, 2, 3, 4, 5};
  cout << "Creating Vector<int> V initialized with {1, 2, 3, 4, 5}" << endl;
  Vector<int> V = {1, 2, 3, 4, 5};
  cout << "Creating List<int> L initialized with {1, 2, 3, 4, 5}" << endl;
  List<int> L = {1, 2, 3, 4, 5};
  
  cout << "\nA.front() = " << A.front() << ", A.back() = " << A.back() <<
                                            "A.size() = " << A.size() << endl;
  cout << "V.front() = " << V.front() << ", V.back() = " << V.back() <<
                                            ", V.size() = " << V.size() << endl;
  cout << "L.front() = " << L.front() << ", L.back() = " << L.back() <<
                                            ", L.size() = " << L.size() << endl;
  
  cout << "\nPrinting A with cout: " << A << endl;
  cout << "Printing V with cout: " << V << endl;
  cout << "Printing L with cout: " << L << endl;
  cout << "\nIncrementing all A, V, L ellements in for range loop" << endl;
  for (auto &a : A) ++a;
  for (auto &a : L) ++a;
  for (auto &a : V) ++a;

  cout << "\nPrinting A with cout: " << A << endl;
  cout << "Printing V with cout: " << V << endl;
  cout << "Printing L with cout: " << L << endl;

  cout << "\nPushing back 9 to V and L" << endl;
  V.push_back(9);
  L.push_back(9);
  cout << "V = " << V << endl;
  cout << "L = " << L << endl;

  cout << "\nPushing front 8 to V and L" << endl;
  V.push_front(8);
  L.push_front(8);
  cout << "V = " << V << endl;
  cout << "L = " << L << endl;

  cout << "\nInserting 7 to V and L (pos = 2)" << endl;
  V.insert(2, 7);
  L.insert(2, 7);
  cout << "V = " << V << endl;
  cout << "L = " << L << endl;

  cout << "\nErasing element with index 1 in V and L" << endl;
  V.erase(1);
  L.erase(1);
  cout << "V = " << V << endl;
  cout << "L = " << L << endl;

  cout << "\nSorting V with std::sort()" << endl;
  std::sort(V.begin(), V.end());
  cout << "V = " << V << endl;
}

int main() {
  cout << "Type \"help\" to get help" << endl;

  string cmd;

  while (cmd != "exit") {
    cin >> cmd;

    if (cmd == "create") create();
    else if (cmd == "ls") ls();
    else if (cmd == "del") del();
    else if (cmd == "append") append();
    else if (cmd == "insert") insert();
    else if (cmd == "remove") remove();
    else if (cmd == "get") get();
    else if (cmd == "set") set();
    else if (cmd == "len") length();
    else if (cmd == "print") print();
    else if (cmd == "help") help();
    else if (cmd == "demo") demo();
  }
}