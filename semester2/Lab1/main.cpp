#include <iostream>
#include "Database.hpp"
#include "Message.hpp"
using namespace std;

int main() {
  Database<Message> db = Database<Message>::Generate(2);

  db.saveToBinFile("hundred.bin");
  db.saveToTextFile("hundred.txt");

  db.loadFromBinFile("hundred.bin");
  db.print();

  db.loadFromTextFile("hundred.txt");
  db.print();
}