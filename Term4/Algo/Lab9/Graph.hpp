#pragma once

#include <set>
#include <vector>
#include <limits>
#include <iostream>
#include <iomanip>

template<typename T = int>
class Graph {
public:
  static constexpr auto MaxValue = std::numeric_limits<T>::max();

  struct Edge {
    size_t vertex;
    T weight;
    Edge(size_t vertex, const T &weight) : vertex(vertex), weight(weight) {}

    bool operator<(const Edge &rhs) const {
      return vertex < rhs.vertex;
    }
  };

  explicit Graph(size_t size = 0) :
      adj(std::vector<std::vector<Edge>>(size)) {}

  void resize(size_t size) {
    adj.resize(size);
  }
  void reserve(size_t size) {
    adj.reserve(size);
  }
  size_t size() const {
    return adj.size();
  }

  auto &getAdj() const {
    return adj;
  }
  auto &getAdj() {
    return adj;
  }


  //add directed edge
  void addEdge(size_t av, size_t bv, const T &weight = 1) {
    adj[av].emplace_back(Edge(bv, weight));
  }
  //add undirected edge
  void connect(size_t av, size_t bv, const T &weight = 1) {
    adj[av].emplace_back(Edge(bv, weight));
    adj[bv].emplace_back(Edge(av, weight));
  }

private:
  std::vector<std::vector<Edge>> adj;
};

template<typename T>
std::ostream &
operator<<(std::ostream &os, const std::vector<std::vector<T>> &matrix) {
  constexpr auto W = 8;
  os << "        ";
  for (int j = 0; j < matrix.size(); ++j) {
    os << std::setw(W) << std::left << j;
  }
  os << std::endl;

  for (int i = 0; i < matrix.size(); ++i) {
    os << std::setw(W) << std::left << i;
    for (int j = 0; j < matrix.size(); ++j) {
      if (matrix[i][j] == Graph<T>::MaxValue)
        os << std::setw(W) << std::left << "INF";
      else if (matrix[i][j] == Graph<T>::MaxValue)
        os << std::setw(W) << std::left << "-INF";
      else
        os << std::fixed << std::setprecision(2)
           << std::setw(W) << std::left << matrix[i][j];
    }

    os << std::endl;
  }
  return os;
}