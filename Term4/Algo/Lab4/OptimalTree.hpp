#pragma once

#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>


class OptimalTree {
private:

  class Node {
  public:
    int value;
    double probability;
    bool mainKey;

    Node *parent;
    Node *left;
    Node *right;

    Node(): left(nullptr), right(nullptr), parent(nullptr) {}

    explicit Node(int value, double probability, bool mainKey):
    value(value), probability(probability), mainKey(mainKey),
    left(nullptr), right(nullptr), parent(nullptr) { }

    ~Node() = default;
  };

  Node *root;

  template<class T>
  using Matrix = std::vector<std::vector<T>>;

  std::vector<double> keys;
  std::vector<double> fictitiousKeys;

  Matrix<double> expectedValue;
  Matrix<int> roots;

  void generateTables() {
    double weights[keys.size() + 1][keys.size()];

    for (int i = 0; i < keys.size() + 1; i++)
      for (int j = 0; j < keys.size(); j++)
        weights[i][j] = 0;

    for (int i = 1; i < keys.size() + 1; i++) {
      expectedValue[i][i - 1] = fictitiousKeys[i - 1];
      weights[i][i - 1] = fictitiousKeys[i - 1];
    }

    for (int k = 1; k < keys.size(); k++) {
      for (int i = 1; i < keys.size() - k + 1; i++) {
        int j = i + k - 1;
        expectedValue[i][j] = INT16_MAX;
        weights[i][j] = weights[i][j - 1] + keys[j] + fictitiousKeys[j];

        for (int r = i; r <= j; r++) {
          double t = expectedValue[i][r - 1] +
                     expectedValue[r + 1][j] +
                     weights[i][j];

          if (t < expectedValue[i][j]) {
            expectedValue[i][j] = t;
            roots[i][j] = r;
          }
        }
      }
    }

    cout << "weights:\n";
    for (int i = 1; i <= keys.size(); i++) {
      for (int j = 0; j <= keys.size() -1; j++)
        cout << weights[i][j] << '\t';
      cout << endl;
    }
    cout << endl;
    cout << "roots:\n";
    for (int i = 1; i <= keys.size() - 1; i++) {
      for (int j = 1; j <= keys.size() - 1; j++)
        cout << roots[i][j] << '\t';
      cout << endl;
    }
    cout << endl;
    cout << "expected value:\n";
    for (int i = 1; i <= keys.size(); i++) {
      for (int j = 0; j <= keys.size() - 1; j++)
        cout << expectedValue[i][j] << '\t';
      cout << endl;
    }
    cout << endl;
  }

  Node *generateTree(int i, int j, Node *parent) {
    if (j == i - 1) {
      return new Node(0, fictitiousKeys[i - 1], false);
    }

    int currentNode = roots[i][j];
    Node *node = new Node(currentNode, keys[currentNode], true);
    node->parent = parent;
    node->left = generateTree(i, currentNode - 1, node);
    node->right = generateTree(currentNode + 1, j, node);

    return node;
  }

public:
  OptimalTree(std::vector<double> keys, std::vector<double> fictitiousKeys):
  expectedValue(Matrix<double>(this->keys.size() + 1, std::vector<double>(this->keys.size()))),
  roots(Matrix<int>(this->keys.size(), std::vector<int>(this->keys.size()))),
  keys(std::move(keys)),
  fictitiousKeys(std::move(fictitiousKeys)),
  root(nullptr) {

    generateTables();
    root = generateTree(1, this->keys.size() - 1, nullptr);
  }

  Node *getRoot() {
    return root;
  }
};