#include <iostream>
#include <vector>
using namespace std;

#include "OptimalTree.hpp"

int main() {
  vector<double> keys1 = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
  vector<double> fictitiousKeys1 = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

  OptimalTree tree1(keys1, fictitiousKeys1);
  cout << tree1;

  vector<double> keys2 = {0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
  vector<double> fictitiousKeys2 = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};

  OptimalTree tree2(keys2, fictitiousKeys2);
  cout << tree2;

  return 0;
}
