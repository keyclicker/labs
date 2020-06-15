#pragma once
#include "Container.hpp"

#include <algorithm>
#include <istream>
#include <iomanip>
#include <vector>
#include <random>
#include <memory>
#include <list>

//Task 18.1
template<typename T>
struct Tree : SortedContainer<T> {
private:
  struct Node {
    T value;
    std::shared_ptr<Tree<T>::Node> left, right;
    explicit Node(const T &val = T()):
            value(val), left(nullptr), right(nullptr) {}
  };

  size_t sz;
  std::shared_ptr<Node> root;

  void insert(const T &val, std::shared_ptr<Node> &node);
  void print(std::ostream &out, std::shared_ptr<Node> node) const;

public:
  explicit Tree(): sz(0), root(nullptr) {}

  T &front() override;
  T &back() override;

  const T &front() const override;
  const T &back() const override;

  [[nodiscard]]
  size_t size() const override;

  void insert(const T &val) override;
  void remove(const T &val) override;
  void clear() override;

  friend std::ostream &operator<<(std::ostream &out, const Tree &val) {
    out << '{';
    val.print(out, val.root);
    out << '}';
    return out;
  }
};

template<typename T>
void Tree<T>::insert(const T &val, std::shared_ptr<Node> &node) {
  if (!node)
    node = std::make_shared<Tree<T>::Node>(val);
  else {
    if (val <= node->value) {
      insert(val, node->left);
    }
    else {
      insert(val, node->right);
    }
  }
}

template<typename T>
void Tree<T>::insert(const T &val) {
  ++sz;
  insert(val, root);
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
  return root->value;
}

template<typename T>
T &Tree<T>::back() {
  return root->value;
}

template<typename T>
const T &Tree<T>::front() const {
  return root->value;
}

template<typename T>
const T &Tree<T>::back() const {
  return root->value;
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
