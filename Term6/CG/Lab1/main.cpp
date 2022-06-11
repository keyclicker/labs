#include <vector>
using namespace std;

#include "Utils.hpp"
#include "RangeTree.hpp"

int main() {
  vector<Point> points = {
    {0, 8},
    {1, 4},
    {3, 9},
    {4, 5},
    {4, 6},
    {5, 10},
    {6, 6},
    {6, 7},
    {8, 6},
    {9, 2}
  };

  auto rt = RangeTree::buildRangeTree(points);
  auto res = rt->search({2, 8.5}, {3, 7.5});

  cout << '\n' << res << endl;
}