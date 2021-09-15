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

      for (auto &a : graph.getAdj()[v]) {
        if (dist[v] + a.weight < dist[a.vertex]) {
          dist[a.vertex] = dist[v] + a.weight;
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
  auto bellmanFord(Graph<T> &graph, size_t v1) {
    std::vector<T> dist(graph.size(), Graph<T>::MaxValue);
    dist[v1] = 0;

    for(int k = 0; k < graph.getAdj().size(); k++) {
      for (int i = 0; i < graph.getAdj().size(); i++) {
        for (int j = 0; j < graph.getAdj()[i].size(); j++) {
          if (graph.getAdj()[i][j].weight + dist[i] < dist[graph.getAdj()[i][j].vertex]
          && dist[i] != Graph<T>::MaxValue) {
            dist[graph.getAdj()[i][j].vertex] = graph.getAdj()[i][j].weight + dist[i];
          }
        }
      }
    }

    return dist;
  }



  template<typename T>
  auto johnsonDistances(Graph<T> &graph) {
    graph.expendGraph();
    auto balances = bellmanFord(graph, graph.size() - 1);
    graph.shrinkGraph();

    for(int i = 0; i < graph.getAdj().size(); i++){
      for(int j = 0; j < graph.getAdj()[i].size(); j++){
        graph.getAdj()[i][j].weight = graph.getAdj()[i][j].weight + balances[i] - balances[graph.getAdj()[i][j].vertex];
      }
    }

    auto result = dijkstra(graph);

    for(int i = 0; i < graph.getAdj().size(); i++){
      for(int j = 0; j < graph.getAdj()[i].size(); j++){
        graph.getAdj()[i][j].weight = graph.getAdj()[i][j].weight - balances[i] + balances[graph.getAdj()[i][j].vertex];
      }
    }

    return result;
  }


}