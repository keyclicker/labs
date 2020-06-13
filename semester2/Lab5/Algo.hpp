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
    bool isCyclic(const Graph<T> &graph, size_t vertex,
                  std::shared_ptr<std::set<size_t>> used =
                  std::make_shared<std::set<size_t>>()) {
      used->insert(vertex);
      for (auto &a : graph.getVertices()[vertex]) {
        if (!used->contains(a.vertex))
          return  isCyclic(graph, a.vertex, used);
        else
          return true;
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
  }

  template<typename T>
  bool isConnected(const Graph<T> &graph) {
    return graph.size() == utils::deepCounting(graph, 0);
  }

  template<typename T>
  bool isTree(const Graph<T> &graph) {
    if (!isConnected(graph)) return false;

    for (int i = 0; i < graph.size(); ++i) {
      if (utils::isCyclic(graph, i))
        return false;
    }
    return true;
  }

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
  void breadthSearchPrint(const MatrixGraph<T> &graph, size_t vertex) {
    std::set<size_t> used;
    used.insert(vertex);
    std::queue<T> q;
    q.push (vertex);
    std::cout << vertex << std::endl;

    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (size_t i = 0; i < graph.size(); ++i) {
        if (!used.contains(graph.getMatrix()[v][i])) {
          used.insert(graph.getMatrix()[v][i]);
          q.push(graph.getMatrix()[v][i]);
          std::cout << graph.getMatrix()[v][i] << std::endl;
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

  template<typename T>
  auto floydWarshall(const Graph<T> &graph) {
    boost::multi_array<T, 2> dist(boost::extents[graph.size()][graph.size()]);
    std::fill(dist.data(), dist.data() + dist.num_elements(), Graph<T>::MaxValue);

    for (int i = 0; i < graph.size(); ++i)
      for (auto a : graph.getVertices()[i])
        dist[i][a.vertex] = a.weight;

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
  auto floydWarshall(const Graph<T> &graph, size_t v1) {
    auto dist = floydWarshall(graph);
    return dist[v1];
  }

  template<typename T>
  auto dijkstra(const Graph<T> &graph, size_t v1) {
    boost::multi_array<T, 1> dist(boost::extents[graph.size()]);
    std::fill(dist.data(), dist.data() + dist.num_elements(), Graph<T>::MaxValue);
    std::set<size_t> used;
    dist[v1] = 0;

    for (int i = 0; i < graph.size(); ++i) {
      size_t v = -1;
      for (int j=0; j< graph.size(); ++j)
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
  auto dijkstra(const Graph<T> &graph) {
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
  auto topologicalSort(const Graph<T> &graph) {
    std::list<T> ans;
    std::set<size_t> used;
    for (int i = 0; i < graph.size(); ++i)
      if (!used.contains(i))
        utils::deepSearchTopological(graph, ans, used, i);
    return ans;
  }


  template<typename T>
  auto spanningTree(const Graph<T> &graph, size_t vertex = 0) {
    Graph<T> spanning(graph.size());
    utils::deepSortSpanning(graph, spanning, vertex);
    return graph;
  }

  template<typename T>
  auto kruskal(const Graph<T> &graph) {

    using EdgeType = std::pair<size_t, typename Graph<T>::Edge>;
    std::vector<EdgeType> g;
    g.reserve(graph.size());
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

    for (int i = 0; i < graph.size(); ++i) {
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
    return graph;
  }
}