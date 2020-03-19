#include "Journal.hpp"

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>\

using namespace std;

map<string, Journal<Message>> cons;

void create() {
  string name;
  size_t size;
  cin >> name >> size;

  cons[name] = Journal<Message>(size);
}

void push() {
  string name, text;
  cin >> name;

  cin.get();
  getline(cin, text);

  cons[name].push(Message(text));
}

void length() {
  string name;
  cin >> name;
  cout << cons[name].size() << endl;
}

void print() {
  string name;
  cin >> name;
  cout << cons[name];
}

void ls() {
  for (auto a : cons) {
    cout << a.first << " : " << a.second.size() << " messages" << endl;
  }
}

void del() {
  string name;
  cin >> name;
  cons.erase(name);
}

void help() {
  constexpr int w = 25;

  cout << setw(w) << left <<
       "create <name> <size>" << "Create journal" << endl;
  cout << setw(w) << left <<
       "del <name>" << "Delete journal" << endl;
  cout << setw(w) << left <<
       "len <name>" << "Get size of journal" << endl;
  cout << setw(w) << left <<
       "print <name>" << "Print journal" << endl;
  cout << setw(w) << left <<
       "push <name> <message>" << "Push message to journal" << endl;
  cout << setw(w) << left <<
       "ls" << "List journals" << endl;
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
    else if (cmd == "ls") ls();
    else if (cmd == "del") del();
    else if (cmd == "push") push();
    else if (cmd == "len") length();
    else if (cmd == "print") print();
    else if (cmd == "help") help();
    else if (cmd == "demo") demo();
  }
}