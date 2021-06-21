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
    cout << a << ' ';
  }
  cout << endl;


  auto bel = Algorithms::bellmanFord(gr, 0);

  for (auto a: bel) {
    cout << a << ' ';
  }
  cout << endl;

  Graph<int> gr1(4);


  gr1.addEdge(0, 1, -2);
  gr1.addEdge(1, 2, 8);
  gr1.addEdge(0, 2, 7);
  gr1.addEdge(2, 1, 3);
  gr1.addEdge(0, 3, 5);
  gr1.addEdge(3, 0, -1);
  gr1.addEdge(1, 3, 6);
  gr1.addEdge(2, 3, -4);


  auto jd = Algorithms::johnsonDistances(gr1);

  cout << jd << endl;

  return 0;
}
