#pragma once

#include <utility>

template<typename Key, typename Value>
class SplayTree {
public:
  using Pair = std::pair<const Key, Value>;

  class Node;

  explicit SplayTree(Node *root = nullptr);
  ~SplayTree();

  const Value &search(const Key &key) const;

  void clear();

  Value &insert(const Key &key, const Value &value);
  void del(const Key &key);

  Value &operator[](const Key &key);

  void print() {
    print(m_Root, 0, false);
  };

  Node *getRoot();

private:
  Node *getMinNode(Node *node) const;
  Node *getMaxNode(Node *node) const;

  Node *getNode(const Key &key);

  void transplant(Node *parent, Node *child);

  Node *rotateLeft(Node *node);
  Node *rotateRight(Node *node);

  void zig(Node *node);
  void zigZag(Node *node);
  void zigZig(Node *node);

  void splay(Node *node);
  void merge(Node *left, Node *right);

private:
  Node *m_Root;
  int m_Size;
};

template<typename Key, typename Value>
class SplayTree<Key, Value>::Node {
public:
  Pair pair;
  Node *parent;
  Node *left;
  Node *right;

  Node(): pair(Key(), Value()) {};

  Node(const Key &key, const Value &value,
       Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr):
      pair(key, value),
      parent(parent), left(left), right(right) {};

  virtual ~Node() {
    delete left;
    delete right;
  };
};

#include "SplayTree.cpp"