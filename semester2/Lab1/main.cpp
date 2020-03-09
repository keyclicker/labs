#include <iostream>
#include "Database.hpp"
#include "Message.hpp"
using namespace std;

int main() {
  Database<Message> db = Database<Message>::Generate(1000);



  db.saveToBinFile("hundred.bin");
  db.saveToTextFile("hundred.txt");

}