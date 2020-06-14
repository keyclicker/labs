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
#define add(a, b, c) s.addEdge(a, b, c), m.addEdge(a, b, c);
  Graph s(6);
  MatrixGraph m(6);

  add(0, 1, 1);
  add(0, 2, 1);
  add(0, 3, 1);
  add(1, 5, 1);
  add(2, 4, 2);
  add(3, 4, 1);

  cout << "========== Task 2 ==========" << endl;
  cout << "Set Graph S:" << endl;
  printList(s.getVertices());

  cout << "\n========== Task 1 ==========" << endl;
  cout << "Matrix Graph M:" << endl;
  printMatrix(m.getVertices());

  cout << "\n========== Task 15 ==========" << endl;
  cout << "Floyd Warshall for S: " << endl;
  printMatrix(Algorithms::floydWarshall(s));
  cout << "\nFloyd Warshall for M: " << endl;
  printMatrix(Algorithms::floydWarshall(m));

  cout << "\n========== Task 14 ==========" << endl;
  cout << "Dijkstra for S: " << endl;
  printMatrix(Algorithms::dijkstra(s));
  cout << "\nDijkstra for M: " << endl;
  printMatrix(Algorithms::dijkstra(m));

  cout << "========== Task 11 ==========" << endl;
  cout << "Deep-first search for S: " << endl;
  Algorithms::deepSearchPrint(s, 0);
  cout << "\nDeep-first search for M: " << endl;
  Algorithms::deepSearchPrint(m, 0);
  cout << endl;

  cout << "========== Task 13 ==========" << endl;
  cout << "Breadth-first search for S: " << endl;
  Algorithms::breadthSearchPrint(s, 0);
  cout << "\nBreadth-first search for M: " << endl;
  Algorithms::breadthSearchPrint(m, 0);
  cout << endl;

  cout << "========== Task 18 ==========" << endl;
  cout << "Topological sort for S: " << endl;
  for (const auto &a : Algorithms::topologicalSort(s)) {
    cout << a << ' ';
  }
  cout << "\nTopological sort for M: " << endl;
  for (const auto &a : Algorithms::topologicalSort(m)) {
    cout << a << ' ';
  }

  cout << "\n\n";
  cout << "========== Task 19 ==========" << endl;
  cout << "Deep Search spanning tree for S:" << endl;
  auto st = Algorithms::spanningTree(s);
  printList(st.graph.getVertices());
  cout << "Cost = " << st.cost << endl;
  cout << "\nDeep Search spanning tree for M:" << endl;
  auto st1 = Algorithms::spanningTree(m);
  printList(st1.graph.getVertices());
  cout << "Cost = " << st1.cost << endl;


  cout << "\n========== Task 21 ==========" << endl;
  cout << "Kruskal minimal spanning tree for S:" << endl;
  auto k = Algorithms::kruskal(s);
  printList(k.graph.getVertices());
  cout << "Cost = " << k.cost << endl;
  cout << "\nKruskal minimal spanning tree for M:" << endl;
  auto k1 = Algorithms::kruskal(m);
  printList(k1.graph.getVertices());
  cout << "Cost = " << k1.cost << endl;

  cout << "\n========= Task 5, 8 =========" << endl;
  cout << "Is S a tree: " << (Algorithms::isTree(s) ? "yes" : "no") << endl;
  cout << "Is S connected: " << (Algorithms::isConnected(s) ? "yes" : "no")<< endl;
  cout << "Is M a tree: " << (Algorithms::isTree(m) ? "yes" : "no") << endl;
  cout << "Is M connected: " << (Algorithms::isConnected(m) ? "yes" : "no")<< endl;
  cout << endl;

#define add(a, b, c) s1.addEdge(a, b, c), m1.addEdge(a, b, c);
  Graph s1(3);
  MatrixGraph m1(3);

  add(0, 1, 1);

  cout << "Set Graph S1:" << endl;
  printList(s1.getVertices());

  cout << "\nMatrix Graph M1:" << endl;
  printMatrix(m1.getVertices());

  cout << "\nIs S1 a tree: " << (Algorithms::isTree(s1) ? "yes" : "no") << endl;
  cout << "Is S1 connected: " << (Algorithms::isConnected(s1) ? "yes" : "no")<< endl;
  cout << "Is M1 a tree: " << (Algorithms::isTree(m1) ? "yes" : "no") << endl;
  cout << "Is M1 connected: " << (Algorithms::isConnected(m1) ? "yes" : "no")<< endl;

  cout << "\nAdding 1->2 edge to S1 and M1\n" << endl;

  add(1, 2, 1);

  cout << "Set Graph S1:" << endl;
  printList(s1.getVertices());

  cout << "\nMatrix Graph M1:" << endl;
  printMatrix(m1.getVertices());


  cout << "\nIs S1 a tree: " << (Algorithms::isTree(s1) ? "yes" : "no") << endl;
  cout << "Is S1 connected: " << (Algorithms::isConnected(s1) ? "yes" : "no")<< endl;
  cout << "Is M1 a tree: " << (Algorithms::isTree(m1) ? "yes" : "no") << endl;
  cout << "Is M1 connected: " << (Algorithms::isConnected(m1) ? "yes" : "no")<< endl;
  cout << endl;


  cout << "\nAdding 2->0 edge to S1 and M1\n" << endl;

  add(2, 0, 1);

  cout << "Set Graph S1:" << endl;
  printList(s1.getVertices());

  cout << "\nMatrix Graph M1:" << endl;
  printMatrix(m1.getVertices());


  cout << "\nIs S1 a tree: " << (Algorithms::isTree(s1) ? "yes" : "no") << endl;
  cout << "Is S1 connected: " << (Algorithms::isConnected(s1) ? "yes" : "no")<< endl;
  cout << "Is M1 a tree: " << (Algorithms::isTree(m1) ? "yes" : "no") << endl;
  cout << "Is M1 connected: " << (Algorithms::isConnected(m1) ? "yes" : "no")<< endl;
  cout << endl;

}
