#include <iostream>
using namespace std;

#include "Graph.hpp"


int main() {
  Graph graph(500);

  graph.addDirEdge(0, 1, 5);
  graph.addDirEdge(0, 2, 3);
  graph.addDirEdge(1, 4, 8);
  graph.addDirEdge(2, 3, 10);
  graph.addDirEdge(3, 4, 7);

  graph.addUndirEdge(0, 3, 20);
  graph.addUndirEdge(1, 3, 30);

  cout << graph.getMatrix() << endl;
  cout << graph.floydWarshall() << endl;
  cout << graph.floydWarshallMulti() << endl;

  return 0;
}
