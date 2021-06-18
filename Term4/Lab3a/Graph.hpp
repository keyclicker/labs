#pragma once

#include <vector>
#include <limits>
#include <thread>
#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <mutex>

template<typename T = int>
class Graph {
private:
  std::vector<std::vector<T>> matrix;

public:
  static constexpr auto Inf = std::numeric_limits<T>::max();

  explicit Graph(size_t size = 0) :
      matrix(std::vector(size,
                         std::vector(size, Inf))) {
    for (int i = 0; i < size; ++i) {
      matrix[i][i] = 0;
    }
  };

  /**
   * Adding directed edge to graph
   * @param a First vertex index
   * @param b Second vertex index
   * @param weight Weight of edge
   */
  void addDirEdge(size_t a, size_t b, T weight) {
    matrix[a][b] = weight;
  }

  /**
  * Adding undirected edge to graph
  * @param a First vertex index
  * @param b Second vertex index
  * @param weight Weight of edge
  */
  void addUndirEdge(size_t a, size_t b, T weight) {
    matrix[a][b] = weight;
    matrix[b][a] = weight;
  }

  /**
  * Getting edge weight
  * @param a First vertex index
  * @param b Second vertex index
  * @return Weight of edge
  */
  auto getEdge(size_t a, size_t b) const {
    return matrix[a][b];
  }

  /**
  * Getting graph matrix
  * @return Graph matrix
  */
  auto getMatrix() const {
    return matrix;
  }

  /**
  * Floyd Warshall
  * @details finds minimal distances from each to each vertex
  * @return distance matrix
  */
  auto floydWarshall() const {
    auto res = matrix;
    for (int k = 0; k < res.size(); ++k)
      for (int i = 0; i < res.size(); ++i)
        for (int j = 0; j < res.size(); ++j)
          if (res[i][k] < Inf && res[k][j] < Inf)
            res[i][j] = std::min(res[i][j], res[i][k] + res[k][j]);

    return res;
  }

  /**
  * Multithreaded Floyd Warshall
  * @details finds minimal distances from each to each vertex
  * @return distance matrix
  */
  auto floydWarshallMulti() const {
    auto res = matrix;

    auto **mm = new std::mutex *[res.size()];
    for (int i = 0; i < res.size(); ++i)
      mm[i] = new std::mutex[res.size()];


    auto threaded = [&res, mm](size_t threadNum, size_t threadCount) mutable {
      size_t chunkSize = std::ceil((float) res.size() / threadCount);

      for (int k = chunkSize * threadNum;
           k < std::min(chunkSize * (threadNum + 1), res.size()); ++k) {
        for (int i = 0; i < res.size(); ++i)
          for (int j = 0; j < res.size(); ++j)
            if (res[i][k] < Inf && res[k][j] < Inf) {
              mm[i][j].lock();
              res[i][j] = std::min(res[i][j], res[i][k] + res[k][j]);
              mm[i][j].unlock();
            }
      }
    };


    auto thrCnt = std::min((size_t) res.size(),
                           (size_t) std::thread::hardware_concurrency());

    std::vector<std::thread *> threads(thrCnt);
    for (int i = 0; i < thrCnt; ++i) {
      threads[i] = new std::thread(threaded, i, thrCnt);
    }

    for (auto a: threads) a->join();

    for (int i = 0; i < res.size(); ++i)
      delete[] mm[i];
    delete[] mm;

    return res;
  }
};

/**
* STL output operator for matrices
* @details outputs matrices
*/
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
      if (matrix[i][j] == Graph<T>::Inf)
        os << std::setw(W) << std::left << "INF";
      else
        os << std::fixed << std::setprecision(2)
           << std::setw(W) << std::left << matrix[i][j];
    }

    os << std::endl;
  }
  return os;
}


