#pragma once

#include <set>
#include <vector>
#include <limits>
#include <boost/multi_array.hpp>


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
    vertices(std::vector<std::set<Edge>>(size)) {}

  void resize(size_t size) {
    vertices.resize(size);
  }
  void reserve(size_t size) {
    vertices.reserve(size);
  }
  size_t size() const {
    return vertices.size();
  }

  const std::vector<std::set<Edge>> &getVertices() const {
    return vertices;
  }
  std::vector<std::set<Edge>> &getVertices() {
    return vertices;
  }

  //add directed edge
  void addEdge(size_t av, size_t bv, const T &weight = 1) {
    vertices[av].insert(Edge(bv, weight));
  }
  //add undirected edge
  void connect(size_t av, size_t bv, const T &weight = 1) {
    vertices[av].insert(Edge(bv, weight));
    vertices[bv].insert(Edge(av, weight));
  }

private:
  std::vector<std::set<Edge>> vertices;
};


template<typename T = int>
class MatrixGraph {
public:
  static constexpr auto MaxValue = std::numeric_limits<T>::max();

  explicit MatrixGraph(size_t size = 0) :
          matrix((boost::extents[size][size])) {}

  void resize(size_t size) {
    matrix.resize((boost::extents[size][size]));
  }
  void reserve(size_t size) {
    matrix.reserve((boost::extents[size][size]));
  }
  size_t size() const {
    return matrix.size();
  }

  const boost::multi_array<T, 2> &getMatrix() const {
    return matrix;
  }
  boost::multi_array<T, 2> &getVertices() {
    return matrix;
  }

  //add directed edge
  void addEdge(size_t av, size_t bv, const T &weight = 1) {
    matrix[av][bv] = weight;
  }
  //add undirected edge
  void connect(size_t av, size_t bv, const T &weight = 1) {
    matrix[av][bv] = weight;
    matrix[bv][av] = weight;
  }

private:
  boost::multi_array<T, 2> matrix;
};