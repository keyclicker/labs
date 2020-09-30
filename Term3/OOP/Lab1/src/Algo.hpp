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
  }

  /**
  * Checking is graph connected
  * @details Works only with undirected graphs
  * @tparam G Graph type
  * @param graph Graph
  * @return Is graph connected
  */
  template<typename G>
  bool isConnected(const G &graph) {
    return graph.size() == utils::deepCounting(graph, 0);
  }

  /**
   * Checking is graph a tree
   * @details Works only with directed graphs
   * @tparam G Graph type
   * @param graph Graph
   * @return Is graph a tree
   */
  template<typename G>
  bool isTree(const G &graph) {
    if (!isConnected(graph)) return false;
    std::set<size_t> used;

    for (int i = 0; i < graph.size(); ++i) {
      if (!used.contains(i) && utils::isCyclic(graph, i, -1, used))
          return false;
    }
    return true;
  }

  /**
   * Calculating distance between v1 to avery other vertex
   * @tparam T Graph weight type
   * @param graph Graph
   * @param v1 Starting vertex
   * @return Array of distances
   */
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

  /**
   * Calculating distance between v1 to avery other vertex
   * @tparam T Graph weight type
   * @param graph Graph
   * @param v1 Starting vertex
   * @return Array of distances
   */
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

  /**
   * Calculating distance between v1 and v2
   * @tparam G Graph type
   * @param graph Graph
   * @param v1 Starting vertex
   * @param v2 Finishing vertex
   * @return Distance between v1 and v2
   */
  template<typename G>
  auto dijkstra(const G &graph, size_t v1, size_t v2) {
    auto d = dijkstra(graph, v1);
    return d[v2];
  }
}