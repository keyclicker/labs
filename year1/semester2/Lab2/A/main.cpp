#include "Vector.hpp"
#include "Array.hpp"
#include "List.hpp"
#include "Container.hpp"
#include "IPv4.hpp"

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

map<string, shared_ptr<DynamicContainer<IPv4>>> cons;

void create() {
  string name, type;
  cin >> name >> type;

  if (type == "-vector") {
    cons[name] =  shared_ptr<DynamicContainer<IPv4>>(new Vector<IPv4>());
  }
  else if (type == "-list") {
    cons[name] =  shared_ptr<DynamicContainer<IPv4>>(new List<IPv4>());
  }
}

void append() {
  string name, IPs;
  cin >> name;

  getline(cin, IPs);
  stringstream st(IPs);

  while (!st.eof()) {
    IPv4 IP;
    st >> IP;
    cons[name]->push_back(IP);
  }
}

void insert() {
  int index;
  string name, IPs;
  cin >> name >> index;

  getline(cin, IPs);
  stringstream st(IPs);
  st << IPs;

  while (!st.eof()) {
    IPv4 IP;
    st >> IP;
    cons[name]->insert(index++, IP);
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
  int index;
  IPv4 IP;
  cin >> name >> index >> IP;
  cons[name]->at(index) = IP;
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
    cout << a.first << " : " << a.second->size() << " IPs" << endl;
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
  "append <name> <IPs>" << "Append IPs" << endl;
  cout << setw(w) << left <<
  "insert <name> <index> <IPs>" << "Insert IPs" << endl;
  cout << setw(w) << left <<
  "remove <name> <index>" << "Remove IP by index" << endl;
  cout << setw(w) << left <<
  "get <name> <index>" << "Get IP by index" << endl;
  cout << setw(w) << left <<
  "set <name> <index> <IP>" << "Set IP by index" << endl;
  cout << setw(w) << left <<
  "help" << "Run help" << endl;
  cout << setw(w) << left <<
  "demo" << "Run demo" << endl;
}

void demo() {
  cout << "Creating Array<IPv4, 5> A initialized with {1.1.1.1, 2.2.2.2, 3.3.3.3, 4.4.4.4, 5.5.5.5}" << endl;
  Array<IPv4, 5> A = {IPv4(1), IPv4(2), IPv4(3), IPv4(4), IPv4(5)};
  cout << "Creating Vector<IPv4> V initialized with {1.1.1.1, 2.2.2.2, 3.3.3.3, 4.4.4.4, 5.5.5.5}" << endl;
  Vector<IPv4> V = {IPv4(1), IPv4(2), IPv4(3), IPv4(4), IPv4(5)};
  cout << "Creating List<IPv4> L initialized with {1.1.1.1, 2.2.2.2, 3.3.3.3, 4.4.4.4, 5.5.5.5}" << endl;
  List<IPv4> L = {IPv4(1), IPv4(2), IPv4(3), IPv4(4), IPv4(5)};
  
  cout << "\nA.front() = " << A.front() << ", A.back() = " << A.back() <<
                                            ", A.size() = " << A.size() << endl;
  cout << "V.front() = " << V.front() << ", V.back() = " << V.back() <<
                                            ", V.size() = " << V.size() << endl;
  cout << "L.front() = " << L.front() << ", L.back() = " << L.back() <<
                                            ", L.size() = " << L.size() << endl;
  
  cout << "\nPrinting A with cout: " << A << endl;
  cout << "Printing V with cout: " << V << endl;
  cout << "Printing L with cout: " << L << endl;
  cout << "\nIncrementing all A, V, L IPs first num in for range loop" << endl;
  for (auto &a : A) ++a[0];
  for (auto &a : L) ++a[0];
  for (auto &a : V) ++a[0];

  cout << "\nPrinting A with cout: " << A << endl;
  cout << "Printing V with cout: " << V << endl;
  cout << "Printing L with cout: " << L << endl;

  cout << "\nPushing back 9.9.9.9 to V and L" << endl;
  V.push_back(9);
  L.push_back(9);
  cout << "V = " << V << endl;
  cout << "L = " << L << endl;

  cout << "\nPushing front 8.8.8.8 to V and L" << endl;
  V.push_front(8);
  L.push_front(8);
  cout << "V = " << V << endl;
  cout << "L = " << L << endl;

  cout << "\nInserting 7.7.7.7 to V and L (pos = 2)" << endl;
  V.insert(2, 7);
  L.insert(2, 7);
  cout << "V = " << V << endl;
  cout << "L = " << L << endl;

  cout << "\nErasing IP with index 1 in V and L" << endl;
  V.erase(1);
  L.erase(1);
  cout << "V = " << V << endl;
  cout << "L = " << L << endl;

  cout << "\nPoping front and back in V and L" << endl;
  V.pop_back();
  V.pop_front();
  L.pop_back();
  L.pop_front();

  cout << "V = " << V << endl;
  cout << "L = " << L << endl;
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