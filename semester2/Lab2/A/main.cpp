#include "Vector.hpp"
#include "Array.hpp"
#include "List.hpp"
#include "Container.hpp"

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>

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

void list() {
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

}

int main() {
  cout << "Type \"help\" to get help" << endl;

  string cmd;

  while (cmd != "exit") {
    cin >> cmd;

    if (cmd == "create") create();
    else if (cmd == "ls") list();
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