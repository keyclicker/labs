#pragma once

template <typename T>
class FibonacciHeap {
private:
  class Node {
  public:
    T value;
    Node *child;
    Node *parent;
    Node *leftBrother;
    Node *rightBrother;
    int degree;
    bool mark;

    bool visited;

    explicit Node(T value):
    value(value), child(nullptr), parent(nullptr), leftBrother(this),
    rightBrother(this), degree(0), mark(false), visited(false) {}
  };

  void addToRootsList(Node *toAdd, bool allLevel);
  void eraseFromRootsList(Node *toDelete);
  Node *heapUnion(Node *toUnite1, Node *toUnite2);
  void consolidate();
  void link(Node *greaterRoot, Node *lesserRoot);
  Node *findNodeByValue(Node *toFind, T value);
  void cut(Node *toCut);
  void cascadingCut(Node *toCut);
  void print(Node *node, int degree);

  Node *head;
  int size{};

public:
  FibonacciHeap(): head(nullptr), size(0) {}

  void insert(T t);
  T min();
  T extractMin();
  void decreaseKey(T toDecrease, T decreased);
  void erase(T value);
  void print();
};

#include "FibonacciHeap.cpp"