#pragma once
#include "Graph.hpp"

#include <queue>
#include <list>
#include <memory>
#include <set>
#include <vector>
#include <limits>
#include <iostream>
#include <boost/multi_array.hpp>

namespace Algorithms {
  namespace utils {
    template<typename T>
    size_t deepCounting(const Graph<T> &graph, size_t vertex,
                        std::shared_ptr<std::set<size_t>> used =
                        std::make_shared<std::set<size_t>>()) {
      size_t usedcnt = 1;
      used->insert(vertex);
      for (auto &a : graph.getVertices()[vertex]) {
        if (!used->contains(a.vertex)) {
          usedcnt += deepCounting(graph, a.vertex, used);
        }
      }
      return usedcnt;
    }

    template<typename T>
    size_t deepCounting(const MatrixGraph<T> &graph, size_t vertex,
                        std::shared_ptr<std::set<size_t>> used =
                        std::make_shared<std::set<size_t>>()) {
      size_t usedcnt = 1;
      used->insert(vertex);
      for (int i = 0; i < graph.size(); ++i) {
        if (!used->contains(i) &&
                graph.getMatrix()[vertex][i] != MatrixGraph<T>::MaxValue) {
          usedcnt += deepCounting(graph, i, used);
        }
      }
      return usedcnt;
    }

    template<typename T>
    bool isCyclic(const Graph<T> &graph, size_t vertex, int64_t parent,
            std::set<size_t> &used) {
      used.insert(vertex);
      for (auto &a : graph.getVertices()[vertex]) {
        if (used.contains(a.vertex) && a.vertex != parent)
          return true;
        else if (a.vertex != parent)
          return isCyclic(graph, a.vertex, vertex, used);
      }
      return false;
    }

    template<typename T>
    bool isCyclic(const MatrixGraph<T> &graph, size_t vertex, int64_t parent,
                  std::set<size_t> &used) {
      used.insert(vertex);
      for (int i = 0; i < graph.size(); ++i) {
        if (i != parent && i != vertex && graph.getMatrix()[vertex][i] !=
        MatrixGraph<T>::MaxValue) {
          if (used.contains(i))
            return true;
          else
            return isCyclic(graph, i, vertex, used);
        }
      }
      return false;
    }

    template<typename T>
    void deepSearchTopological(const Graph<T> &graph, std::list<T> &ans,
                               std::set<size_t> &used, size_t vertex) {
      used.insert(vertex);
      for (auto &a : graph.getVertices()[vertex]) {
        if (!used.contains(a.vertex))
          deepSearchTopological(graph, ans, used, a.vertex);
      }
      ans.push_front(vertex);
    }

    template<typename T>
    void deepSearchTopological(const MatrixGraph<T> &graph, std::list<T> &ans,
                               std::set<size_t> &used, size_t vertex) {
      used.insert(vertex);
      for (size_t i = 0; i < graph.size(); ++i) {
        if (!used.contains(i) && graph.getMatrix()[vertex][i] !=
                                  MatrixGraph<T>::MaxValue)
          deepSearchTopological(graph, ans, used, i);
      }
      ans.push_front(vertex);
    }

    template<typename T>
    void deepSortSpanning(const Graph<T> &graph, Graph<T> &spanning, size_t vertex,
                          std::shared_ptr<std::set<size_t>> used =
                          std::make_shared<std::set<size_t>>()) {
      used->insert(vertex);
      for (auto a : graph.getVertices()[vertex]) {
        if (!used->contains(a.vertex)) {
          spanning.addEdge(vertex, a.vertex, a.weight);
          deepSortSpanning(graph, spanning, a.vertex, used);
        }
      }
    }

    template<typename T>
    void deepSortSpanning(const MatrixGraph<T> &graph, Graph<T> &spanning, size_t vertex,
                          std::shared_ptr<std::set<size_t>> used =
                          std::make_shared<std::set<size_t>>()) {
      used->insert(vertex);
      for (size_t i = 0; i < graph.size(); ++i) {
        if (!used->contains(i) && graph.getMatrix()[vertex][i] !=
                                 MatrixGraph<T>::MaxValue) {
          spanning.addEdge(vertex, i, graph.getMatrix()[vertex][i]);
          deepSortSpanning(graph, spanning, i, used);
        }
      }
    }
  }

  //--------------------- Task 5 -----------------------------------------------

  template<typename T>
  bool isConnected(const Graph<T> &graph) {
    return graph.size() == utils::deepCounting(graph, 0);
  }

  template<typename T>
  bool isConnected(const MatrixGraph<T> &graph) {
    return graph.size() == utils::deepCounting(graph, 0);
  }

  //--------------------- Task 8 -----------------------------------------------

  template<typename T>
  bool isTree(const Graph<T> &graph) {
    if (!isConnected(graph)) return false;
    std::set<size_t> used;

    for (int i = 0; i < graph.size(); ++i) {
      if (!used.contains(i) && utils::isCyclic(graph, i, -1, used))
          return false;
    }
    return true;
  }

  template<typename T>
  bool isTree(const MatrixGraph<T> &graph) {
    if (!isConnected(graph)) return false;
    std::set<size_t> used;

    for (int i = 0; i < graph.size(); ++i) {
      if (!used.contains(i) && utils::isCyclic(graph, i, -1, used))
        return false;
    }
    return true;
  }

  //--------------------- Task 11 ----------------------------------------------

  template<typename T>
  void deepSearchPrint(const Graph<T> &graph, size_t vertex,
                        std::shared_ptr<std::set<size_t>> used =
                        std::make_shared<std::set<size_t>>()) {
    used->insert(vertex);
    std::cout << vertex << ' ';
    for (auto a : graph.getVertices()[vertex]) {
      if (!used->contains(a.vertex))
        deepSearchPrint(graph, a.vertex, used);
    }
  }

  template<typename T>
  void deepSearchPrint(const MatrixGraph<T> &graph, size_t vertex,
                       std::shared_ptr<std::set<size_t>> used =
                       std::make_shared<std::set<size_t>>()) {
    used->insert(vertex);
    std::cout << vertex << ' ';
    for (size_t i = 0; i < graph.size(); ++i) {
      if (!used->contains(i) && graph.getMatrix()[vertex][i] !=
      MatrixGraph<T>::MaxValue)
        deepSearchPrint(graph, i, used);
    }
  }

  //--------------------- Task 13 ----------------------------------------------

  template<typename T>
  void breadthSearchPrint(const MatrixGraph<T> &graph, size_t vertex) {
    std::set<size_t> used;
    used.insert(vertex);
    std::queue<T> q;
    q.push (vertex);
    std::cout << vertex << ' ';

    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (size_t i = 0; i < graph.size(); ++i) {
        if (!used.contains(i) && graph.getMatrix()[v][i] !=
        MatrixGraph<T>::MaxValue) {
          used.insert(i);
          q.push(i);
          std::cout << i << ' ';
        }
      }
    }
  }

  template<typename T>
  void breadthSearchPrint(const Graph<T> &graph, size_t vertex) {
    std::set<size_t> used;
    used.insert(vertex);
    std::queue<size_t> q;
    q.push (vertex);
    std::cout << vertex << ' ';

    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto &a : graph.getVertices()[v]) {
        if (!used.contains(a.vertex)) {
          used.insert(a.vertex);
          q.push(a.vertex);
          std::cout << a.vertex << ' ';
        }
      }
    }
  }

  //--------------------- Task 15 ----------------------------------------------

  template<typename T>
  auto floydWarshall(const Graph<T> &graph) {
    boost::multi_array<T, 2> dist(boost::extents[graph.size()][graph.size()]);
    std::fill(dist.data(), dist.data() + dist.num_elements(), Graph<T>::MaxValue);

    for (int i = 0; i < graph.size(); ++i) {
      dist[i][i] = 0;
      for (auto a : graph.getVertices()[i])
        dist[i][a.vertex] = a.weight;
    }

    for (int i = 0; i < graph.size(); ++i)
      for (int j = 0; j < graph.size(); ++j)
        for (int k = 0; k < graph.size(); ++k)
          if (dist[i][k] != Graph<T>::MaxValue && dist[k][j] != Graph<T>::MaxValue)
            dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);

    return dist;
  }

  template<typename T>
  auto floydWarshall(const MatrixGraph<T> &graph) {
    boost::multi_array<T, 2> dist = graph.getMatrix();

    for (int i = 0; i < graph.size(); ++i)
      for (int j = 0; j < graph.size(); ++j)
        for (int k = 0; k < graph.size(); ++k)
          if (dist[i][k] != Graph<T>::MaxValue && dist[k][j] != Graph<T>::MaxValue)
            dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);

    return dist;
  }

  template<typename T>
  T floydWarshall(const Graph<T> &graph, size_t v1, size_t v2) {
    auto dist = floydWarshall(graph);
    return dist[v1][v2];
  }

  template<typename T>
  T floydWarshall(const MatrixGraph<T> &graph, size_t v1, size_t v2) {
    auto dist = floydWarshall(graph);
    return dist[v1][v2];
  }

  template<typename T>
  auto floydWarshall(const Graph<T> &graph, size_t v1) {
    auto dist = floydWarshall(graph);
    return dist[v1];
  }

  template<typename T>
  auto floydWarshall(const MatrixGraph<T> &graph, size_t v1) {
    auto dist = floydWarshall(graph);
    return dist[v1];
  }

  //--------------------- Task 14 ----------------------------------------------

  template<typename T>
  auto dijkstra(const Graph<T> &graph, size_t v1) {
    boost::multi_array<T, 1> dist(boost::extents[graph.size()]);
    std::fill(dist.data(), dist.data() + dist.num_elements(), Graph<T>::MaxValue);
    std::set<size_t> used;
    dist[v1] = 0;

    for (int i = 0; i < graph.size(); ++i) {
      size_t v = -1;
      for (int j = 0; j < graph.size(); ++j)
        if (!used.contains(j) && (v == -1 || dist[j] < dist[v]))
          v = j;
      if (dist[v] == Graph<T>::MaxValue)
        break;
      used.insert(v);

      for (auto &a : graph.getVertices()[v]) {
        if (dist[v] + a.weight < dist[a.vertex]) {
          dist[a.vertex] = dist[v] + a.weight;
        }
      }
    }
    return dist;
  }

  template<typename T>
  auto dijkstra(const MatrixGraph<T> &graph, size_t v1) {
    boost::multi_array<T, 1> dist(boost::extents[graph.size()]);
    std::fill(dist.data(), dist.data() + dist.num_elements(), Graph<T>::MaxValue);
    std::set<size_t> used;
    dist[v1] = 0;

    for (int i = 0; i < graph.size(); ++i) {
      size_t v = -1;
      for (int j = 0; j < graph.size(); ++j)
        if (!used.contains(j) && (v == -1 || dist[j] < dist[v]))
          v = j;
      if (dist[v] == Graph<T>::MaxValue)
        break;
      used.insert(v);

      for (int k = 0; k < graph.size(); ++k) {
        if (dist[v] +  graph.getMatrix()[v][k] < dist[k] &&
        graph.getMatrix()[v][k] != MatrixGraph<T>::MaxValue) {
          dist[k] = dist[v] + graph.getMatrix()[v][k];
        }
      }
    }
    return dist;
  }

  template<typename T>
  auto dijkstra(const Graph<T> &graph) {
    boost::multi_array<T, 2> d(boost::extents[graph.size()][graph.size()]);
    for (int i = 0; i < graph.size(); ++i) {
      d[i] = dijkstra(graph, i);
    }
    return d;
  }

  template<typename T>
  auto dijkstra(const MatrixGraph<T> &graph) {
    boost::multi_array<T, 2> d(boost::extents[graph.size()][graph.size()]);
    for (int i = 0; i < graph.size(); ++i) {
      d[i] = dijkstra(graph, i);
    }
    return d;
  }

  template<typename T>
  auto dijkstra(const Graph<T> &graph, size_t v1, size_t v2) {
    auto d = dijkstra(graph, v1);
    return d[v2];
  }

  template<typename T>
  auto dijkstra(const MatrixGraph<T> &graph, size_t v1, size_t v2) {
    auto d = dijkstra(graph, v1);
    return d[v2];
  }

  //--------------------- Task 18 ----------------------------------------------

  template<typename T>
  auto topologicalSort(const Graph<T> &graph) {
    std::list<T> ans;
    std::set<size_t> used;
    for (int i = 0; i < graph.size(); ++i)
      if (!used.contains(i))
        utils::deepSearchTopological(graph, ans, used, i);
    return ans;
  }

  template<typename T>
  auto topologicalSort(const MatrixGraph<T> &graph) {
    std::list<T> ans;
    std::set<size_t> used;
    for (int i = 0; i < graph.size(); ++i)
      if (!used.contains(i))
        utils::deepSearchTopological(graph, ans, used, i);
    return ans;
  }

  //--------------------- Task 19 ----------------------------------------------

  template<typename T>
  auto spanningTree(const Graph<T> &graph, size_t vertex = 0) {
    Graph<T> spanning(graph.size());
    utils::deepSortSpanning(graph, spanning, vertex);
    return spanning;
  }

  template<typename T>
  auto spanningTree(const MatrixGraph<T> &graph, size_t vertex = 0) {
    Graph<T> spanning(graph.size());
    utils::deepSortSpanning(graph, spanning, vertex);
    return spanning;
  }

  //--------------------- Task 21 ----------------------------------------------

  template<typename T>
  auto kruskal(const Graph<T> &graph) {
    using EdgeType = std::pair<size_t, typename Graph<T>::Edge>;
    std::vector<EdgeType> g;
    g.reserve(graph.size()*graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      for (auto a : graph.getVertices()[i]) {
        g.push_back(std::make_pair(i, a));
      }
    }
    sort(g.begin(), g.end(), [](EdgeType &a, EdgeType &b) {
      return a.second.weight < b.second.weight;
    });

    std::vector<size_t> tree_id(graph.size());
    for (int i = 0; i < graph.size(); ++i)
      tree_id[i] = i;

    Graph<T> spanning(graph.size());
    T cost = 0;

    for (int i = 0; i < g.size(); ++i) {
      size_t a = g[i].first, b = g[i].second.vertex;
      T l = g[i].second.weight;

      if (tree_id[a] != tree_id[b]) {
        cost += l;
        spanning.addEdge(a, b, l);
        for (auto &j : tree_id)
          if (j == tree_id[b])
            j = tree_id[a];
      }
    }
    struct Spanning {Graph<T> graph; T cost; };
    return Spanning {spanning, cost};
  }

  template<typename T>
  auto kruskal(const MatrixGraph<T> &graph) {
    struct Edge {
      size_t v1, v2;
      T weight;
    };
    std::vector<Edge> g;
    g.reserve(graph.size()*graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      for (int j = 0; j < graph.size(); ++j) {
        if (graph.getMatrix()[i][j] != MatrixGraph<T>::MaxValue)
          g.push_back(Edge{i, j, graph.getMatrix()[i][j]});
      }
    }
    sort(g.begin(), g.end(), [](Edge &a, Edge &b) {
      return a.weight < b.weight;
    });

    std::vector<size_t> tree_id(graph.size());
    for (int i = 0; i < graph.size(); ++i)
      tree_id[i] = i;

    Graph<T> spanning(graph.size());
    T cost = 0;

    for (int i = 0; i < g.size(); ++i) {
      size_t a = g[i].v1, b = g[i].v2;
      T l = g[i].weight;

      if (tree_id[a] != tree_id[b]) {
        cost += l;
        spanning.addEdge(a, b, l);
        for (auto &j : tree_id)
          if (j == tree_id[b])
            j = tree_id[a];
      }
    }
    struct Spanning {Graph<T> graph; T cost; };
    return Spanning {spanning, cost};
  }
}