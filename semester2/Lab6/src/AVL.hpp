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
class AvlTree: SortedContainer<T> {
private:
  struct Node {
    T value;
    size_t height;
    std::shared_ptr<AvlTree<T>::Node> left, right, parent;
    explicit Node(std::shared_ptr<AvlTree<T>::Node> parent, const T &val = T()):
        value(val), height(1), left(nullptr), right(nullptr), parent(parent) {}
  };

public:
  class iterator;

  AvlTree(const AvlTree &rhs) = delete;
  AvlTree<T> &operator=(const AvlTree &rhs) = delete;

  AvlTree(AvlTree &&rhs) noexcept;
  AvlTree<T> &operator=(AvlTree &&rhs) noexcept;

  explicit AvlTree(): sz(0),
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

  friend std::ostream &operator<<(std::ostream &out, const AvlTree &val) {
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
  auto rightRotate(std::shared_ptr<Node> y);
  auto leftRotate(std::shared_ptr<Node> x);
  void insert(const T &val,
              std::shared_ptr<Node> &node,  std::shared_ptr<Node> parent);

};

template<typename T>
auto AvlTree<T>::rightRotate(std::shared_ptr<Node> y) {
  std::shared_ptr<Node> x = y->left;
  std::shared_ptr<Node> T2 = x ? x->right : nullptr;

  if (x) x->right = y;
  if (y) y->parent = x;
  y->left = T2;
  if (T2) T2->parent = y;

  static auto height = [](std::shared_ptr<Node> &n) {return n ? n->height : 0;};
  if (y) y->height = std::max(height(y->left), height(y->right)) + 1;
  if (x) x->height = std::max(height(x->left), height(x->right)) + 1;

  return x;
}

template<typename T>
auto AvlTree<T>::leftRotate(std::shared_ptr<Node> x) {
  std::shared_ptr<Node> y = x->right;
  std::shared_ptr<Node> T2 = y ? y->left : nullptr;

  if (y) y->left = x;
  if (x) x->parent = y;
  x->right = T2;
  if (T2) T2->parent = x;

  static auto height = [](std::shared_ptr<Node> &n) {return n ? n->height : 0;};
  if (x) x->height = std::max(height(x->left), height(x->right)) + 1;
  if (y) y->height = std::max(height(y->left), height(y->right)) + 1;

  return y;
}

template<typename T>
void AvlTree<T>::insert(const T &val,
                     std::shared_ptr<Node> &node, std::shared_ptr<Node> parent) {
  if (!node) {
    ++sz;
    node = std::make_shared<AvlTree<T>::Node>(parent, val);
  }
  else {
    if (val < node->value) {
      insert(val, node->left, node);
    }
    else if (val > node->value) {
      insert(val, node->right, node);
    }
  }

  static auto height = [](std::shared_ptr<Node> &n) {return n ? n->height : 0;};

  node->height = 1 + std::max(height(node->left),
                         height(node->right));

  int balance = (int) height(node->left) - height(node->right);

  if (balance > 1 && val < node->left->value)
    node = rightRotate(node);
  else if (balance < -1 && val > node->right->value)
    node = leftRotate(node);
  else if (balance > 1 && val > node->left->value) {
    node->left = leftRotate(node->left);
    node->left->parent = node;
    node = rightRotate(node);
  }
  else if (balance < -1 && val < node->right->value) {
    node->right = rightRotate(node->right);
    node->right->parent = node;
    node = leftRotate(node);
  }
  node->parent = parent;
}

template<typename T>
void AvlTree<T>::insert(const T &val) {
  insert(val, root->left, root);
}

template<typename T>
void AvlTree<T>::print(std::ostream &out, std::shared_ptr<Node> node) const {
  if (node) {
    print(out, node->left);
    out << node->value << (node != (--end()).node ? ", " : "");
    print(out, node->right);
  }
}

template<typename T>
T AvlTree<T>::front() const {
  auto i = root->left;
  while (i->left) i = i->left;
  return i->value;
}

template<typename T>
T AvlTree<T>::back() const {
  auto i = root->left;
  while (i->right) i = i->right;
  return i->value;
}

template<typename T>
size_t AvlTree<T>::size() const {
  return sz;
}

template<typename T>
void AvlTree<T>::remove(const T &val) {
  auto fnd = find(val);
  if (fnd != end()) erase(fnd);
}

template<typename T>
void AvlTree<T>::clear() {

}

template<typename T>
AvlTree<T>::AvlTree(AvlTree &&rhs) noexcept: root(rhs.root), sz(rhs.sz) {
  rhs.root = nullptr;
  rhs.sz = 0;
}

template<typename T>
AvlTree<T> &AvlTree<T>::operator=(AvlTree &&rhs) noexcept {
  root = rhs.root;
  sz = rhs.sz;
  rhs.root = nullptr;
  rhs.sz = 0;
}


template<typename T>
typename AvlTree<T>::iterator AvlTree<T>::begin() const {
  auto i = root;
  while (i->left) i = i->left;
  return iterator(i);
}

template<typename T>
typename AvlTree<T>::iterator AvlTree<T>::end() const {
  return iterator(root);
}

template<typename T>
typename AvlTree<T>::iterator
AvlTree<T>::find(const T &val, std::shared_ptr<Node> node) const {
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
typename AvlTree<T>::iterator
AvlTree<T>::find(const T &val) const {
  return find(val, root->left);
}

template<typename T>
typename AvlTree<T>::iterator
AvlTree<T>::find(const T &min, const T &max, std::shared_ptr<Node> node) const {
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
typename AvlTree<T>::iterator
AvlTree<T>::find(const T &min, const T &max) const {
  return find(min, max, root->left);
}

template<typename T>
class AvlTree<T>::iterator :
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
void AvlTree<T>::erase(iterator pos) {
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


  static auto height = [](std::shared_ptr<Node> &n) {return n ? n->height : 0;};

  pos.node->parent->height = 1 + std::max(height(pos.node->parent->left),
                                      height(pos.node->parent->right));

  pos.node->height = 1 + std::max(height(pos.node->left),
                              height(pos.node->right));

  int balance = (int) height(pos.node->left) - height(pos.node->right);

  std::shared_ptr<Node> n = pos.node->parent;
  auto val = pos.node->value;

  if (balance > 1 && val < pos.node->left->value)
    pos.node = rightRotate(pos.node);
  else if (balance < -1 && val > pos.node->right->value)
    pos.node = leftRotate(pos.node);
  else if (balance > 1 && val > pos.node->left->value) {
    pos.node->left = leftRotate(pos.node->left);
    if (pos.node->left) pos.node->left->parent = pos.node;
    pos.node = rightRotate(pos.node);
  }
  else if (balance < -1 && val < pos.node->right->value) {
    pos.node->right = rightRotate(pos.node->right);
    if (pos.node->right) pos.node->right->parent = pos.node;
    pos.node = leftRotate(pos.node);
  }
  if (pos.node) pos.node->parent = n;
}

