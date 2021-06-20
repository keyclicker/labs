#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

#include "HashTable.hpp"

int main() {
  vector<pair<string, string>> vocabulary = {
      {"Cow", "Korova"},
      {"Bread", "Hlib"},
      {"Cat", "Kit"},
      {"Vocabulary", "Slovnyk"},
      {"Table", "Tablycya"},
  };

  HashTable ht(vocabulary);

  cout << ht << endl;

  cout << "In Ukrainian \"Vocabulary\" is " << ht["Vocabulary"] << endl;

  return 0;
}
