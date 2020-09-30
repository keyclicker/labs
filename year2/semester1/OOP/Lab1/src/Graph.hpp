#pragma once

#include <set>
#include <vector>
#include <limits>
#include <boost/multi_array.hpp>

/**
 * Adjacency list graph
 * @tparam T Weight type
 */
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

  /**
   * Constructor
   * @param size vertices count
   */
  explicit Graph(size_t size = 0) :
          vertices(std::vector<std::set<Edge>>(size)) {}

  /**
   * Changes vertices count
   * @param size vertices count
   */
  void resize(size_t size) {
    vertices.resize(size);
  }

  /**
   * @return Vertices count
   */
  size_t size() const {
    return vertices.size();
  }

  /**
   * @return Adjacency list
   */
  const std::vector<std::set<Edge>> &getVertices() const {
    return vertices;
  }

  /**
   * @return Adjacency list
   */
  std::vector<std::set<Edge>> &getVertices() {
    return vertices;
  }

  /**
   * Adds directed edge
   * @param av First vertex
   * @param bv Second vertex
   * @param weight Weight of the edge
   */
  void addEdge(size_t av, size_t bv, const T &weight = 1) {
    vertices[av].insert(Edge(bv, weight));
  }

  /**
   * Adds undirected edge
   * @param av First vertex
   * @param bv Second vertex
   * @param weight Weight of the edge
   */
  void connect(size_t av, size_t bv, const T &weight = 1) {
    vertices[av].insert(Edge(bv, weight));
    vertices[bv].insert(Edge(av, weight));
  }

  /**
   * Returns weight of the edge
   * @param av first vertex
   * @param bv second vertex
   * @return Edge weight
   */
  T getEdge(size_t av, size_t bv) {
    return vertices[av].find(Edge(bv, 0))->weight;
  }

private:
  std::vector<std::set<Edge>> vertices;
};

/**
 * Adjacency matrix graph
 * @tparam T Weight type
 */
template<typename T = int>
class MatrixGraph {
public:
  static constexpr auto MaxValue = std::numeric_limits<T>::max();

  explicit MatrixGraph(size_t size = 0) :
          matrix((boost::extents[size][size])) {
    std::fill(matrix.data(), matrix.data() +
                             matrix.num_elements(), MatrixGraph<T>::MaxValue);
    for (int i = 0; i < size; ++i) {
      matrix[i][i] = 0;
    }
  }

  /**
   * Changes vertices count
   * @param size vertices count
   */
  void resize(size_t size) {
    matrix.resize((boost::extents[size][size]));
  }

  /**
   * @return Vertices count
   */
  size_t size() const {
    return matrix.size();
  }

  /**
   * @return Adjacency matrix
   */
  const boost::multi_array<T, 2> &getMatrix() const {
    return matrix;
  }

  /**
* @return Adjacency matrix
*/
  boost::multi_array<T, 2> &getVertices() {
    return matrix;
  }

  /**
   * Adds directed edge
   * @param av First vertex
   * @param bv Second vertex
   * @param weight Weight of the edge
   */
  void addEdge(size_t av, size_t bv, const T &weight = 1) {
    matrix[av][bv] = weight;
  }

  /**
  * Adds undirected edge
  * @param av First vertex
  * @param bv Second vertex
  * @param weight Weight of the edge
  */
  void connect(size_t av, size_t bv, const T &weight = 1) {
    matrix[av][bv] = weight;
    matrix[bv][av] = weight;
  }

  /**
   * Returns weight of the edge
   * @param av first vertex
   * @param bv second vertex
   * @return Edge weight
   */
  T getEdge(size_t av, size_t bv) {
    return matrix[av][bv];
  }

private:
  boost::multi_array<T, 2> matrix;
};