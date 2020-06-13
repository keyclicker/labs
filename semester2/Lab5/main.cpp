#include "Graph.hpp"
#include "Algo.hpp"

#include <iostream>
#include <iomanip>
using namespace std;

template<typename T>
void printMatrix(T matrix) {
  for (const auto &a : matrix) {
    for (auto b : a) {
      if (b == Graph<int>::MaxValue)
        cout << "INF ";
      else
        cout << setw(3) << b << ' ';
    }
    cout << endl;
  }
}

template<typename T>
void printList(T matrix) {
  cout << "(vertex, weight)";
  int i = 0;
  for (const auto &a : matrix) {
    cout << '\n' << i++ << ": ";
    for (const auto &b : a)
      cout << '(' << setw(2) << b.vertex << ',' << setw(2)<< b.weight << ") ";
  }
  cout << endl;
}

int main() {
  Graph g(4);
  g.addEdge(0, 1, 1);
  g.addEdge(1, 2, 1);
 // g.addEdge(0, 2, 1);
  g.addEdge(2, 0);

  cout << "Graph G:" << endl;
  printList(g.getVertices());

  cout << "\nFloyd Warshall: " << endl;
  printMatrix(Algorithms::floydWarshall(g));

  cout << "\nDijkstra: " << endl;
  printMatrix(Algorithms::dijkstra(g));

  cout << "\nTree: " << (Algorithms::isTree(g) ? "yes" : "no") << endl;
  cout << "Connected: " << (Algorithms::isConnected(g) ? "yes" : "no")<< endl;
  cout << endl;

  cout << "Deep-first search: " << endl;
  Algorithms::deepSearchPrint(g, 0);
  cout << endl;

  cout << "Breadth-first search: " << endl;
  Algorithms::breadthSearchPrint(g, 0);
  cout << endl;

  cout << "Topological sort: " << endl;
  for (const auto &a : Algorithms::topologicalSort(g)) {
    cout << a << ' ';
  }
  cout << "\n\n";

  printList(Algorithms::spanningTree(g).getVertices());
  cout << "\n";
  printList(Algorithms::kruskal(g).getVertices());


}
