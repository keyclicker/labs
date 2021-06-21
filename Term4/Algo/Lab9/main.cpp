#include <iostream>
using namespace std;

#include "Graph.hpp"
#include "Algorithms.hpp"

int main() {
  Graph<int> gr(4);

  gr.addEdge(0, 2, 1);
  gr.addEdge(1, 2, 2);
  gr.addEdge(1, 3, 20);
  gr.addEdge(1, 4, 4);
  gr.addEdge(0, 3, 1);
  gr.addEdge(2, 3, 9);
  gr.addEdge(1, 5, 3);
  gr.addEdge(3, 4, 4);

  auto dis = Algorithms::dijkstra(gr, 0);

  for (auto a: dis) {
    cout << a << ' ' << endl;
  }


  auto bel = Algorithms::dijkstra(gr, 0);

  for (auto a: bel) {
    cout << a << ' ' << endl;
  }
  
  return 0;
}
