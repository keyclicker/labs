#include "interactive.hpp"
#include "Database.hpp"
#include "Message.hpp"
#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string, Database<Message>> databases;


void interactive() {
  cout << "Welcome to Lab1 interactive mode!"<< endl;
  cout << "print \"help\" to get list of commands with descriptions"<< endl;

  string cmd;
  while (cmd != "exit") {
    cin >> cmd;

    if (cmd == "send") send();
    else if (cmd == "ls") ls();
    else if (cmd == "lsdb") lsdb();
    else if (cmd == "edit") edit();
    else if (cmd == "help") help();
    else if (cmd == "load") load();
    else if (cmd == "save") save();
    else if (cmd == "demo") demo();
    else if (cmd == "create") create();
    else if (cmd == "deldb") deldb();
    else if (cmd == "del") del();
    else if (cmd == "gen") gen();
    else help();
  }
}

void lsdb() {
  for (auto a : databases) {
    cout << a.first << ": " << a.second.getData().size() << " messages" << endl;
  }
}

void create() {
  string name;
  cin >> name;
  databases.insert(make_pair(name, Database<Message>()));
}

void deldb() {
  string name;
  cin >> name;
  databases.erase(name);
}

void help () {
  cout << "create -database_name-" << endl;
  cout << "delete -database_name-" << endl;
  cout << "lsdb -database_name-" << endl;
}

void send() {

}

void edit() {

}

void load() {
  string name, mode, path;
  cin >> name >> mode >> path;
  if (mode == "-t")
    databases[name].loadFromTextFile(path);
  else if (mode == "-b")
    databases[name].loadFromBinFile(path);
  else
    help();
}

void save() {
  string name, mode, path;
  cin >> name >> mode >> path;
  if (mode == "-t")
    databases[name].saveToTextFile(path);
  else if (mode == "-b")
    databases[name].saveToBinFile(path);
  else
    help();
}

void demo() {

}

void ls() {
  string name;
  cin >> name;
  databases[name].print();
}

void del() {
  string name;
  size_t id;
  cin >> name >> id;
  databases[name].getData().erase(std::next(databases[name].getData().begin(), id));
};

void gen() {
  string name;
  int count;
  cin >> name >> count;
  databases[name] = Database<Message>::Generate(count);
}