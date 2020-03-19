#include "Set.hpp"

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

map<string, Set<int>> cons;

void create() {
  string name;
  size_t size;
  cin >> name >> size;

  cons[name] = Set<int>();
}

void insert() {
  string name, vals;
  cin >> name;

  getline(cin, vals);
  stringstream st(vals);

  while (!st.eof()) {
    int val;
    st >> val;
    cons[name].insert(val);
  }
}

void length() {
  string name;
  cin >> name;
  cout << cons[name].size() << endl;
}

void print() {
  string name;
  cin >> name;
  cout << cons[name] << endl;
}

void ls() {
  for (auto a : cons) {
    cout << a.first << " : " << a.second.size() << " elements" << endl;
  }
}

void del() {
  string name;
  cin >> name;
  cons.erase(name);
}

void add() {
  string a, b, c;
  cin >> c >> a >> b;
  cons[c] = cons[a] + cons[b];
}

void sub() {
  string a, b, c;
  cin >> c >> a >> b;
  cons[c] = cons[a] - cons[b];
}

void XOR() {
  string a, b, c;
  cin >> c >> a >> b;
  cons[c] = cons[a] ^ cons[b];
}

void intersection() {
  string a, b, c;
  cin >> c >> a >> b;
  cons[c] = cons[a] | cons[b];
}

void contains() {
  string name;
  int value;
  cin >> name >> value;
  cout << (cons[name].contains(value) ? "yes" : "no") << endl;
}

void help() {
  constexpr int w = 25;

  cout << setw(w) << left <<
       "create <name>" << "Create set" << endl;
  cout << setw(w) << left <<
       "del <name>" << "Delete set" << endl;
  cout << setw(w) << left <<
       "len <name>" << "Get size of set" << endl;
  cout << setw(w) << left <<
       "print <name>" << "Print set" << endl;
  cout << setw(w) << left <<
       "insert <name> <values>" << "Push message to set" << endl;
  cout << setw(w) << left <<
       "contains <name> <value>" << "Check is value in set" << endl;
  cout << setw(w) << left <<
       "add <c> <a> <b>" << "c = a + b" << endl;
  cout << setw(w) << left <<
       "sub <c> <a> <b>" << "c = a - b" << endl;
  cout << setw(w) << left <<
       "int <c> <a> <b>" << "c = a | b (intersection)" << endl;
  cout << setw(w) << left <<
       "xor <c> <a> <b>" << "c = a ^ b (exclusive or)" << endl;
  cout << setw(w) << left <<
       "ls" << "List sets" << endl;
  cout << setw(w) << left <<
       "help" << "Run help" << endl;
  cout << setw(w) << left <<
       "demo" << "Run demo" << endl;
}

void demo() {
  cout << "Set<int> a = {1, 2, 3, 4, 5};" << endl;
  Set<int> a = {1, 2, 3, 4, 5};
  cout << "Set<int> b = {3, 4, 5, 6, 7};" << endl;
  Set<int> b = {3, 4, 5, 6, 7};
  cout << "Set<int> c;" << endl;
  Set<int> c;
  cout << "\nc = a + b;" << endl;
  c = a + b;
  cout << "c = " << c << endl;

  cout << "c = a - b;" << endl;
  c = a - b;
  cout << "c = " << c << endl;

  cout << "c = b - a;" << endl;
  c = b - a;
  cout << "c = " << c << endl;

  cout << "c = a | b;" << endl;
  c = a | b;
  cout << "c = " << c << endl;

  cout << "c = a ^ b;" << endl;
  c = a ^ b;
  cout << "c = " << c << endl;

  cout << "\nc.contains(1) = " << c.contains(1) << endl;
  cout << "c.contains(3) = " << c.contains(3) << endl;
  cout << "c.contains(5) = " << c.contains(5) << endl;
  cout << "c.contains(6) = " << c.contains(6) << endl;
}

int main() {
  cout << "Type \"help\" to get help" << endl;

  string cmd;

  while (cmd != "exit") {
    cin >> cmd;

    if (cmd == "create") create();
    else if (cmd == "ls") ls();
    else if (cmd == "del") del();
    else if (cmd == "insert") insert();
    else if (cmd == "contains") contains();
    else if (cmd == "add") add();
    else if (cmd == "sub") sub();
    else if (cmd == "int") intersection();
    else if (cmd == "xor") XOR();
    else if (cmd == "len") length();
    else if (cmd == "print") print();
    else if (cmd == "help") help();
    else if (cmd == "demo") demo();
  }
}