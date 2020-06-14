#include "Graph.hpp"
#include "Algo.hpp"

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <map>
#include <boost/multi_array.hpp>
using namespace std;

void graph();
void graphm();
void print();
void printm();
void add();
void addm();
void iscon();
void isconm();
void istree();
void istreem();
void dfs();
void dfsm();
void bfs();
void bfsm();
void floyd();
void floydm();
void dijkstra();
void dijkstram();
void topsrt();
void topsrtm();
void span();
void spanm();
void krus();
void krusm();

void help();
void demo();

map<string, shared_ptr<Graph<int>>> gs;
map<string, shared_ptr<MatrixGraph<int>>> mgs;

int main() {
  cout << "Type \"help\" to get help" << endl;

  string cmd;

  while (cmd != "exit") {
    cin >> cmd;

    if (cmd ==  "graph") graph ();
    else if (cmd == "graphm") graphm();
    else if (cmd == "add") add();
    else if (cmd == "addm") addm();
    else if (cmd == "print") print();
    else if (cmd == "printm") printm();
    else if (cmd == "iscon") iscon();
    else if (cmd == "isconm") isconm();
    else if (cmd == "istree") istree();
    else if (cmd == "istreem") istreem();
    else if (cmd == "dfs") dfs();
    else if (cmd == "dfsm") dfsm();
    else if (cmd == "bfs") bfs();
    else if (cmd == "bfsm") bfsm();
    else if (cmd == "floyd") floyd();
    else if (cmd == "floydm") floydm();
    else if (cmd == "dijkstra") dijkstra();
    else if (cmd == "dijkstram") dijkstram();
    else if (cmd == "topsrt") topsrt();
    else if (cmd == "topsrtm") topsrtm();
    else if (cmd == "span") span();
    else if (cmd == "spanm") spanm();
    else if (cmd == "krus") krus();
    else if (cmd == "krusm") krusm();
    else if (cmd == "help") help();
  }
}

void help() {
  constexpr int w = 35;

  cout << R"('<command_name>' - for set graph)" << endl;
  cout << R"('<command_name>' + 'm' - for matrix graph)" << endl;
  cout << R"('add' for set graph and 'addm' for matrix graph)" << endl;
  cout << endl;

  cout << setw(w) << left <<
       "graph <name>" << "Create set/matrix graph" << endl;
  cout << setw(w) << left <<
       "add <name> <v1> <v2> <weight>" << "Add edge to graph" << endl;
  cout << setw(w) << left <<
       "print <name>" << "Print graph>" << endl;
  cout << setw(w) << left <<
       "iscon <name>" << "Is graph connected" << endl;
  cout << setw(w) << left <<
       "istree <name>" << "Is graph a tree" << endl;
  cout << setw(w) << left <<
       "dfs <name>" << "Print all vertices with DFS" << endl;
  cout << setw(w) << left <<
       "bfs <name>" << "Print all vertices with BFS" << endl;
  cout << setw(w) << left <<
       "floyd <name>" << "Print matrix of distance with Floyd Warshall" << endl;
  cout << setw(w) << left <<
       "dijkstra <name>" << "Print matrix of distance with Dijkstra Algo" << endl;
  cout << setw(w) << left <<
       "topsrt <name>" << "Print all vertices sorted with Topology Sort" << endl;
  cout << setw(w) << left <<
       "span <name>" << "Print spanning graph build with DFS" << endl;
  cout << setw(w) << left <<
       "krus <name>" << "Print min spanning graph build with Kruskal" << endl;
}

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

void graph() {
  string name;
  int size;
  cin >> name >> size;
  gs[name] = std::make_shared<Graph<int>>(size);
}

void graphm() {
  string name;
  int size;
  cin >> name >> size;
  mgs[name] = std::make_shared<MatrixGraph<int>>(size);
}

void print() {
  string name;
  cin >> name;
  printList(gs[name]->getVertices());
}

void printm() {
  string name;
  cin >> name;
  printMatrix(mgs[name]->getMatrix());
}

void add() {
  string name;
  int v1, v2, weight;
  cin >> name >> v1 >> v2 >> weight;
  gs[name]->addEdge(v1, v2, weight);
}

void addm() {
  string name;
  int v1, v2, weight;
  cin >> name >> v1 >> v2 >> weight;
  mgs[name]->addEdge(v1, v2, weight);
}

void iscon() {
  string name;
  cin >> name;
  cout << (Algorithms::isConnected(*gs[name]) ? "yes" : "no") << endl;
}

void isconm() {
  string name;
  cin >> name;
  cout << (Algorithms::isConnected(*mgs[name]) ? "yes" : "no") << endl;
}

void istree() {
  string name;
  cin >> name;
  cout << (Algorithms::isTree(*gs[name]) ? "yes" : "no") << endl;
}

void istreem() {
  string name;
  cin >> name;
  cout << (Algorithms::isTree(*mgs[name]) ? "yes" : "no") << endl;
}

void dfs() {
  string name;
  cin >> name;
  Algorithms::deepSearchPrint(*gs[name], 0);
  cout << endl;
}

void dfsm() {
  string name;
  cin >> name;
  Algorithms::deepSearchPrint(*mgs[name], 0);
  cout << endl;
}

void bfs() {
  string name;
  cin >> name;
  Algorithms::breadthSearchPrint(*gs[name], 0);
  cout << endl;
}

void bfsm() {
  string name;
  cin >> name;
  Algorithms::breadthSearchPrint(*mgs[name], 0);
  cout << endl;
}

void floyd() {
  string name;
  cin >> name;
  printMatrix(Algorithms::floydWarshall(*gs[name]));
}

void floydm() {
  string name;
  cin >> name;
  printMatrix(Algorithms::floydWarshall(*mgs[name]));
}

void dijkstra() {
  string name;
  cin >> name;
  printMatrix(Algorithms::dijkstra(*gs[name]));
}

void dijkstram() {
  string name;
  cin >> name;
  printMatrix(Algorithms::dijkstra(*mgs[name]));
}

void topsrt() {
  string name;
  cin >> name;
  for (const auto &a : Algorithms::topologicalSort(*gs[name])) {
    cout << a << ' ';
  }
  cout << endl;
}

void topsrtm() {
  string name;
  cin >> name;
  for (const auto &a : Algorithms::topologicalSort(*mgs[name])) {
    cout << a << ' ';
  }
  cout << endl;
}

void span() {
  string name;
  cin >> name;
  auto k = Algorithms::spanningTree(*gs[name]);
  printList(k.graph.getVertices());
  cout << "Cost = " << k.cost << endl;
}

void spanm() {
  string name;
  cin >> name;
  auto k = Algorithms::spanningTree(*mgs[name]);
  printList(k.graph.getVertices());
  cout << "Cost = " << k.cost << endl;
}

void krus() {
  string name;
  cin >> name;
  auto k = Algorithms::kruskal(*gs[name]);
  printList(k.graph.getVertices());
  cout << "Cost = " << k.cost << endl;
}

void krusm() {
  string name;
  cin >> name;
  auto k = Algorithms::kruskal(*mgs[name]);
  printList(k.graph.getVertices());
  cout << "Cost = " << k.cost << endl;
}
