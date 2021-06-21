#include <queue>
#include <list>
#include <memory>
#include <set>
#include <vector>
#include <limits>
#include <iostream>

namespace Algorithms {
  template<typename T>
  auto dijkstra(const Graph<T> &graph, size_t v1) {
    std::vector<T> dist(graph.size(), Graph<T>::MaxValue);
    std::set<size_t> used;
    dist[v1] = 0;

    for (int i = 0; i < graph.size(); ++i) {
      size_t v = -1;
      for (int j = 0; j < graph.size(); ++j)
        if (used.find(j) == used.end() && (v == -1 || dist[j] < dist[v]))
          v = j;
      if (dist[v] == Graph<T>::MaxValue)
        break;
      used.insert(v);

      for (int k = 0; k < graph.size(); ++k) {
        if (dist[v] +  graph.getMatrix()[v][k] < dist[k] &&
            graph.getMatrix()[v][k] != Graph<T>::MaxValue) {
          dist[k] = dist[v] + graph.getMatrix()[v][k];
        }
      }
    }
    return dist;
  }

  template<typename T>
  auto dijkstra(const Graph<T> &graph) {
    std::vector dist(graph.size(), std::vector<T>(graph.size(), Graph<T>::MaxValue));
    for (int i = 0; i < graph.size(); ++i) {
      dist[i] = dijkstra(graph, i);
    }
    return dist;
  }

  template<typename T>
  auto bellmanFord(const Graph<T> &graph, size_t v1) {
    std::vector<T> dist(graph.size(), Graph<T>::MaxValue);
    dist[v1] = 0;

    for(int k = 0; k < graph.size(); k++) {
      for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
          if (graph.get(i,j) + dist[i] < dist[j]) {
            dist[j] = graph.get(i,j) + dist[i];
          }
        }
      }
    }

    return dist;
  }

  template<typename T>
  auto johnsonDistances(Graph<T> &graph, size_t v1) {
    auto balances = bellmanFord(graph, graph.size() -1);

    for(int i = 0; i < graph.size(); i++){
      for(int j = 0; j < graph.size(); j++){
         graph.addEdge(i, j, graph.get(i, j) + balances[i] - balances[j]);
      }
    }

    auto result = dijkstra(graph);

    for(int i = 0; i < graph.size(); i++){
      for(int j = 0; j < graph.size(); j++){
        graph.addEdge(i, j, graph.get(i, j) - balances[i] + balances[j]);
      }
    }

    return result;
  }


}