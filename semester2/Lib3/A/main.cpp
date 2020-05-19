#include "sorting.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  std::vector<int> a = {1,5,2,4,3};

  sorting::quicksort(a.begin(), a.end());

  for (auto i : a)
    cout << i << ' ';

  return 0;
}