#include <iostream>
#include "Database.hpp"
#include "Message.hpp"
using namespace std;

int main() {
  cout << (Time{05, 05, 05, 22, 05, 2000} > Time{05, 05, 05, 22, 05, 200});

  Database<Message> db = Database<Message>::Generate(10000);

  db.sentAfter(Time{05, 05, 05, 22, 05, 2000}).print();
}