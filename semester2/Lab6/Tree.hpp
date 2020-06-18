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

template<typename T>
class Tree: SortedContainer<T> {
private:
  struct Node {
    T value;
    std::shared_ptr<Tree<T>::Node> left, right, parent;
    explicit Node(std::shared_ptr<Tree<T>::Node> parent, const T &val = T()):
            value(val), left(nullptr), right(nullptr), parent(parent) {}
  };

public:
  class iterator;

  Tree(const Tree &rhs) = delete;
  Tree<T> &operator=(const Tree &rhs) = delete;

  Tree(Tree &&rhs) noexcept;
  Tree<T> &operator=(Tree &&rhs) noexcept;

  explicit Tree(): sz(0),
  root(new Node(nullptr, std::numeric_limits<T>::max())) {}

  T front() const override;
  T back() const override;

  [[nodiscard]]
  size_t size() const override;

  void insert(const T &val) override;
  void remove(const T &val) override;
  void clear() override;

  iterator begin() const;
  iterator end() const;

  iterator find(const T &val) const;
  iterator find(const T &min, const T &max) const;
  void erase(iterator pos);

  friend std::ostream &operator<<(std::ostream &out, const Tree &val) {
    out << '{';
    val.print(out, val.root->left);
    out << '}';
    return out;
  }

private:
  size_t sz;
  std::shared_ptr<Node> root;

  iterator find(const T &val, std::shared_ptr<Node> node) const;
  iterator find(const T &min, const T &max, std::shared_ptr<Node> node) const;
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
  if (node) {
    print(out, node->left);
    out << node->value << (node != (--end()).node ? ", " : "");
    print(out, node->right);
  }
}

template<typename T>
T Tree<T>::front() const {
  auto i = root->left;
  while (i->left) i = i->left;
  return i->value;
}

template<typename T>
T Tree<T>::back() const {
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
  iterator rem;
  while ((rem = find(val)) != end())
    erase(rem);
}

template<typename T>
void Tree<T>::clear() {

}

template<typename T>
Tree<T>::Tree(Tree &&rhs) noexcept: root(rhs.root), sz(rhs.sz) {
  rhs.root = nullptr;
  rhs.sz = 0;
}

template<typename T>
Tree<T> &Tree<T>::operator=(Tree &&rhs) noexcept {
  root = rhs.root;
  sz = rhs.sz;
  rhs.root = nullptr;
  rhs.sz = 0;
}


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

template<typename T>
typename Tree<T>::iterator
Tree<T>::find(const T &val, std::shared_ptr<Node> node) const {
  if (node) {
    if (node->value == val)
      return iterator(node);
    else if (val <= node->value)
      return find(val, node->left);
    else
      return find(val, node->right);
  }
  return iterator(root);
}

template<typename T>
typename Tree<T>::iterator
Tree<T>::find(const T &val) const {
  return find(val, root->left);
}

template<typename T>
typename Tree<T>::iterator
Tree<T>::find(const T &min, const T &max, std::shared_ptr<Node> node) const {
  if (node) {
    if (min <= node->value && node->value <= max)
      return iterator(node);
    else if (max <= node->value)
      return find(min, max, node->left);
    else
      return find(min, max, node->right);
  }
  return iterator(root);
}

template<typename T>
typename Tree<T>::iterator
Tree<T>::find(const T &min, const T &max) const {
  return find(min, max, root->left);
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

  iterator(): node(nullptr) {};
  explicit iterator(std::shared_ptr<Node> node): node(node) {};

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
void Tree<T>::erase(iterator pos) {
  --sz;
  if (pos.node->left && pos.node->right) {
    auto suc = pos; ++suc;
    pos.node->value = suc.node->value;

    if (suc.node->parent->left == suc.node)
      suc.node->parent->left = nullptr;
    else if (suc.node->parent->right == suc.node)
      suc.node->parent->right = nullptr;
  }
  else {
    std::shared_ptr<Node> node;
    if (!pos.node->left && !pos.node->right)
      node = nullptr;
    else if (pos.node->left && !pos.node->right)
      node = pos.node->left;
    else if (!pos.node->left && pos.node->right)
      node = pos.node->right;

    if (node) node->parent = pos.node->parent;
    if (pos.node->parent->left == pos.node)
      pos.node->parent->left = node;
    else if (pos.node->parent->right == pos.node)
      pos.node->parent->right = node;
  }
}

