#pragma once
#include "Container.hpp"

#include <algorithm>
#include <istream>
#include <iomanip>
#include <vector>
#include <random>
#include <memory>
#include <limits>
#include <list>

//Task 18.1
template<typename T>
struct Tree : SortedContainer<T> {
public:
  class iterator;

  explicit Tree(): sz(0),
  root(new Node(nullptr, std::numeric_limits<T>::max())) {}

  T &front() override;
  T &back() override;

  const T &front() const override;
  const T &back() const override;

  [[nodiscard]]
  size_t size() const override;

  void insert(const T &val) override;
  void remove(const T &val) override;
  void clear() override;

  iterator begin() const;
  iterator end() const;

  friend std::ostream &operator<<(std::ostream &out, const Tree &val) {
    out << '{';
    val.print(out, val.root->left);
    out << '}';
    return out;
  }

private:
  struct Node {
    T value;
    std::shared_ptr<Tree<T>::Node> left, right, parent;
    explicit Node(std::shared_ptr<Tree<T>::Node> parent, const T &val = T()):
            value(val), left(nullptr), right(nullptr), parent(parent) {}
  };

  size_t sz;
  std::shared_ptr<Node> root;

  void print(std::ostream &out, std::shared_ptr<Node> node) const;
  void insert(const T &val,
              std::shared_ptr<Node> &node,  std::shared_ptr<Node> parent);
};

template<typename T>
void Tree<T>::insert(const T &val,
        std::shared_ptr<Node> &node, std::shared_ptr<Node> parent) {
  if (!node)
    node = std::make_shared<Tree<T>::Node>(parent, val);
  else {
    if (val <= node->value) {
      insert(val, node->left, node);
    }
    else {
      insert(val, node->right, node);
    }
  }
}

template<typename T>
void Tree<T>::insert(const T &val) {
  ++sz;
  insert(val, root->left, root);
}

template<typename T>
void Tree<T>::print(std::ostream &out, std::shared_ptr<Node> node) const {
  static int64_t sz = this->sz;
  if (node) {
    if (!sz) sz = this->sz;
    print(out, node->left);
    out << node->value << (--sz ? ", " : "");
    print(out, node->right);
  }
}


template<typename T>
T &Tree<T>::front() {
  auto i = root->left;
  while (i->left) i = i->left;
  return i->value;
}

template<typename T>
T &Tree<T>::back() {
  auto i = root->left;
  while (i->right) i = i->right;
  return i->value;
}

template<typename T>
const T &Tree<T>::front() const {
  auto i = root->left;
  while (i->left) i = i->left;
  return i->value;
}

template<typename T>
const T &Tree<T>::back() const {
  auto i = root->left;
  while (i->right) i = i->right;
  return i->value;
}

template<typename T>
size_t Tree<T>::size() const {
  return sz;
}

template<typename T>
void Tree<T>::remove(const T &val) {

}

template<typename T>
void Tree<T>::clear() {

}

template<typename T>
class Tree<T>::iterator :
        public std::iterator<std::bidirectional_iterator_tag, T> {
private:
  void inc() {
    if (node->right) {
      node = node->right;
      while (node->left) node = node->left;
    }
    else if (node->parent) {
      if (node->parent->left == node) {
        node = node->parent;
      }
      else if (node->parent->right == node) {
        while (node->parent ? node->parent->right == node : false)
          node = node->parent;
        node = node->parent;
      }
    }
  }

  void dec() {
    if (node->left) {
      node = node->left;
      while (node->right) node = node->right;
    }
    else if (node->parent) {
      if (node->parent->right == node) {
        node = node->parent;
      }
      else if (node->parent->left == node) {
        while (node->parent ? node->parent->left == node : false)
          node = node->parent;
        node = node->parent;
      }
    }
  }

public:
  std::shared_ptr<Node> node;

  explicit iterator(std::shared_ptr<Node> node) : node(node) {};

  iterator(const iterator &val) = default;

  iterator &operator++() {
    inc();
    return *this;
  }
  iterator &operator--() {
    dec();
    return *this;
  }
  iterator operator++(int) {
    auto tmp = *this;
    inc();
    return tmp;
  }
  iterator operator--(int) {
    auto tmp = *this;
    dec();
    return tmp;
  }
  T *operator->() const {
    return &node->value;
  }
  T &operator*() const {
    return node->value;
  };

  friend bool operator==(const iterator &it1, const iterator &it2) {
    return it1.node == it2.node;
  }
  friend bool operator!=(const iterator &it1, const iterator &it2) {
    return it1.node != it2.node;
  }
};

template<typename T>
typename Tree<T>::iterator Tree<T>::begin() const {
  auto i = root;
  while (i->left) i = i->left;
  return iterator(i);
}

template<typename T>
typename Tree<T>::iterator Tree<T>::end() const {
  return iterator(root);
}

