#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;


template<typename T>
class Matrix {
private:
  vector<vector<T>> matrix;

public:
  Matrix defaultMultiplication(const Matrix &b) {
    Matrix res(getISize(), b.getJSize());

    for (int i = 0; i < res.getISize(); ++i) {
      for (int j = 0; j < res.getJSize(); ++j) {
        for (int k = 0; k < getJSize(); ++k) {
          res.matrix[i][j] += matrix[i][k] * b.matrix[k][j];
        }
      }
    }
    return res;
  }

  Matrix strassenMultiply(const Matrix &b, std::size_t threshold = 64) {
    auto n = b.getJSize();

    if (n <= threshold) return *this * b;

    Matrix c(n, n);
    int k = n / 2;

    Matrix A11(k, k);
    Matrix A12(k, k);
    Matrix A21(k, k);
    Matrix A22(k, k);
    Matrix B11(k, k);
    Matrix B12(k, k);
    Matrix B21(k, k);
    Matrix B22(k, k);

    for (int i = 0; i < k; i++)
      for (int j = 0; j < k; j++) {
        A11.matrix[i][j] = matrix[i][j];
        A12.matrix[i][j] = matrix[i][k + j];
        A21.matrix[i][j] = matrix[k + i][j];
        A22.matrix[i][j] = matrix[k + i][k + j];
        B11.matrix[i][j] = b.matrix[i][j];
        B12.matrix[i][j] = b.matrix[i][k + j];
        B21.matrix[i][j] = b.matrix[k + i][j];
        B22.matrix[i][j] = b.matrix[k + i][k + j];
      }

    auto P1 = A11.strassenMultiply(B12 - B22, threshold);
    auto P2 = (A11 + A12).strassenMultiply(B22, threshold);
    auto P3 = (A21 + A22).strassenMultiply(B11, threshold);
    auto P4 = A22.strassenMultiply(B21 - B11, threshold);
    auto P5 = (A11 + A22).strassenMultiply(B11 + B22, threshold);
    auto P6 = (A12 - A22).strassenMultiply(B21 + B22, threshold);
    auto P7 = (A11 - A21).strassenMultiply(B11 + B12, threshold);

    auto C11 = (P5 + P4 + P6) - P2;
    auto C12 = P1 + P2;
    auto C21 = P3 + P4;
    auto C22 = (P5 + P1) - P3 - P7;

    for (int i = 0; i < k; i++)
      for (int j = 0; j < k; j++) {
        c.matrix[i][j] = C11.matrix[i][j];
        c.matrix[i][j + k] = C12.matrix[i][j];
        c.matrix[k + i][j] = C21.matrix[i][j];
        c.matrix[k + i][k + j] = C22.matrix[i][j];
      }

    return c;
  }

public:
  Matrix(size_t is, size_t js):
          matrix(vector<vector<T>>(is, vector<T>(js, 0))) {}

  Matrix(const vector<vector<T>> &matrix) : matrix(matrix) {}

  Matrix() = default;


  size_t getISize() const {
    return matrix.size();
  }

  size_t getJSize() const {
    return matrix[0].size();
  }


  T get(size_t i, size_t j) const {
    return matrix[i][j];
  }

  void set(size_t i , size_t j, const T &value) {
    matrix[i][j] = value;
  }

  friend std::ostream& operator<<(std::ostream& out, const Matrix<T> &matrix) {
    for (auto &a: matrix.matrix) {
      out << "|";
      for (auto &b: a) {
        out << setw(5) << b;
      }
      out << " |" << endl;
    }
    return out;
  }

  bool operator==(const Matrix &b) {
    for (int i = 0; i < getISize(); ++i)
      for (int j = 0; j < getJSize(); ++j)
        if (matrix[i][j] != b.matrix[i][j])
          return false;

    return true;
  }

  Matrix operator+(const Matrix &b) {
    Matrix res(getISize(), getJSize());
    for (int i = 0; i < getISize(); ++i)
      for (int j = 0; j < getJSize(); ++j)
        res.matrix[i][j] = matrix[i][j] + b.matrix[i][j];

    return res;
  }

  Matrix operator-(const Matrix &b) {
    Matrix res(getISize(), getJSize());
    for (int i = 0; i < getISize(); ++i)
      for (int j = 0; j < getJSize(); ++j)
        res.matrix[i][j] = matrix[i][j] - b.matrix[i][j];

    return res;
  }

  Matrix operator*(const Matrix &b) {
    return defaultMultiplication(b);
  }
};
