#pragma once

#include <algorithm>
#include <list>
#include <map>
using namespace std;

void push(map<int, list<int>> &indexList, int value) {
  indexList[value%100].push_back(value);
}

bool contains(map<int, list<int>> &indexList, int value) {
  return (find(indexList[value%100].begin(),
          indexList[value%100].end(), value) != indexList[value%100].end());
}
