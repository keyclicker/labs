#include "Voronoi.hpp"

int main() {
  Voronoi v({
    {5, 6},
    {7, 8},
    {3, 1},
    {1, 3},
    {2, 2},
    {6, 4},
    {2, 5},
  });

  v.run();
  v.printOutput();
}