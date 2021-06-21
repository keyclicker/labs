#pragma once

#include <set>
#include <vector>
#include <limits>

template<typename T = int>
class Graph {
public:
  static constexpr auto MaxValue = std::numeric_limits<T>::max();
  using Matrix = std::vector<std::vector<T>>;

  explicit Graph(size_t size = 0) :
      matrix(Matrix(size, std::vector<T>(size, MaxValue))) {
    for (int i = 0; i < size; ++i) {
      matrix[i][i] = 0;
    }
  }

  void resize(size_t size) {
    matrix.resize(size);
    for (auto a: matrix)
      a.resize(size);
  }
  void reserve(size_t size) {
    matrix.reserve(size);
    for (auto a: matrix)
      a.reserve(size);
  }
  size_t size() const {
    return matrix.size();
  }

  const auto &getMatrix() const {
    return matrix;
  }
  auto &getVertices() {
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

  auto &get(size_t a, size_t b) {
    return matrix[a][b];
  }
private:
  Matrix matrix;
};