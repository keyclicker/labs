#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

#include "HashTable.hpp"

int main() {
  vector<pair<string, string>> albums = {
      {"Cream", "Wheels of Fire"},
      {"The Doors", "Morrison Hotel"},
      {"Beatles", "Revolver"},
      {"Love", "Forever Changes"},
      {"Pink Floyd", "The Wall"},
  };

  HashTable ht(albums);

  cout << ht << endl;

  cout << "The record store has one The Doors album in stock - " << ht["The Doors"] << endl;

  return 0;
}
