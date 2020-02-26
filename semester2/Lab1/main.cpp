#include <iostream>
#include "Database.hpp"
#include "Message.hpp"

using namespace std;

int main()
{
  Database<Message> db;

  db.loadFromTextFile("load.txt");
  db.print();

  db.saveToTextFile("save.txt");
  db.saveToBinFile("save.bin");

  cout << "Hey, this is from bin file!!" << endl;
  db.loadFromBinFile("save.bin");
  db.print();
}