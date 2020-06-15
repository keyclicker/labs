#pragma once

#include "Container.hpp"
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T>
class List : public SortedContainer<T> {
public:
  class iterator;
  
  List() = default;

  List(const List &ls);
  List<T> &operator=(const List &ls);

  List(List &&ls) noexcept ;
  List<T> &operator=(List &&ls) noexcept;

  virtual ~List();

  T &front() override;
  T &back() override;

  const T &front() const override;
  const T &back() const override;
  [[nodiscard]] size_t size() const override;

  void insert(const T &val) override;
  void remove(const T &val) override;
  void clear() override;

  iterator find(const T &val);
  iterator find(const T &min, const T &max);

  iterator begin() const;
  iterator end() const;

  void print() const;

  friend std::ostream& operator<<(std::ostream& out, const List &val) {
    if (val.sz) {
      out << '{';
      for (auto i = val.begin(); i != --val.end(); ++i) {
        out << *i << ", ";
      }
      out << val.back() << "}";
    }
    else {
      out << "{}";
    }
    return out;
  }

private:
  struct Node {
    T value;
    Node *prev, *next;

    Node() : value(T()), prev(nullptr), next(nullptr) {}
    Node(const T& value, Node *prev , Node *next) :
            value(value), prev(prev), next(next) {}
  };

  size_t sz = 0;
  Node *end_ = new Node();
  Node *begin_ = end_;

  iterator getSortedPos(const T &val, size_t size, iterator begin, iterator end);
  void erase(iterator pos);
  iterator find(const T &val, size_t size, iterator begin, iterator end);
  iterator find(const T &min, const T &max,
                size_t size, iterator begin, iterator end);
};

template<typename T>
class List<T>::iterator :
        public std::iterator<std::bidirectional_iterator_tag, T> {
public:
  Node *node;

  iterator() : node(new Node()) {};
  explicit iterator(Node *node) : node(node) {};

  iterator(const iterator &val) = default;

  iterator &operator++() {
    node = node->next;
    return *this;
  }
  iterator &operator--() {
    node = node->prev;
    return *this;
  }
  iterator operator++(int) {
    node = node->next;
    return iterator(node->prev);
  }
  iterator operator--(int) {
    node = node->prev;
    return iterator(node->next);
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
T &List<T>::front() {
  return begin_->value;
}

template<typename T>
T &List<T>::back() {
  return end_->prev->value;
}

template<typename T>
const T &List<T>::front() const {
  return begin_->value;
}

template<typename T>
const T &List<T>::back() const {
  return end_->prev->value;
}

template<typename T>
typename List<T>::iterator List<T>::begin() const {
  return iterator(begin_);
}

template<typename T>
typename List<T>::iterator List<T>::end() const {
  return iterator(end_);
}

template<typename T>
size_t List<T>::size() const {
  return sz;
}

template<typename T>
void List<T>::clear() {
  sz = 0;
  for (auto i = begin_; i != end_; i = i->next) {
    delete i;
  }
  begin_ = end_;
}

template<typename T>
List<T>::~List() {
  for (auto i = begin_; i != end_; i = i->next) {
    delete i;
  }
  delete end_;
}

template<typename T>
List<T>::List(const List &ls) {
  for (auto i = ls.begin_; i != ls.end_; i = i->next) {
    push_back(i->value);
  }
}

template<typename T>
List<T> &List<T>::operator=(const List &ls) {
  if (*this == ls) return *this;
  clear();
  for (auto i = ls.begin_; i != ls.end_; i = i->next) {
    push_back(i->value);
  }
  return *this;
}

template<typename T>
void List<T>::print() const {
  std::cout << *this << std::endl;
}

template<typename T>
void List<T>::erase(iterator pos) {
  --sz;
  if (pos.node->prev) pos.node->prev->next = pos.node->next;
  if (pos.node->prev) pos.node->next->prev = pos.node->prev;
  delete pos.node;
}

template<typename T>
List<T>::List(List &&ls) noexcept: sz(ls.sz), end_(ls.end_), begin_(ls.begin_) {
  ls.begin_ = ls.end_ = new Node();
  ls.sz = 0;
}

template<typename T>
List<T> &List<T>::operator=(List &&ls) noexcept {
  begin_ = ls.begin_;
  end_ = ls.end_;
  sz = ls.sz_;
  ls.begin_ = ls.end_ = new Node();
  ls.sz = 0;
}

template<typename T>
void List<T>::insert(const T &val) {
  iterator pos = getSortedPos(val, size(), begin(), end());
  ++sz;
  if (pos.node == begin_) {
    begin_ = new Node(val, nullptr, begin_);
    begin_->next->prev = begin_;
  }
  else {
    pos.node = new Node(val, pos.node->prev, pos.node);
    pos.node->prev->next = pos.node;
    pos.node->next->prev = pos.node;
  }
}

template<typename T>
void List<T>::remove(const T &val) {
  iterator i;
  while ((i = find(val)) != end())
    erase(find(val));
}

template<typename T>
typename List<T>::iterator List<T>::find(const T &val) {
  return find(val, sz, begin(), end());
}

template<typename T>
typename List<T>::iterator
List<T>::find(const T &min, const T &max) {
  return find(min, max, sz, begin(), end());
}

template<typename T>
typename List<T>::iterator List<T>
::find(const T &val, size_t size, List::iterator begin, List::iterator end) {
  auto sz = size / 2;
  iterator mid = begin;
  for (int i = 0; i < sz; ++i) ++mid;

  if (*mid == val)
    return mid;
  else if (size <= 0)
    return this->end();
  else if (val < *mid)
    return find(val, sz, begin, ++mid);
  else
    return find(val, size - sz - 1, ++mid, end);
}

template<typename T>
typename List<T>::iterator List<T>
::find(const T &min, const T &max,
        size_t size, List::iterator begin, List::iterator end) {
  auto sz = size / 2;
  iterator mid = begin;
  for (int i = 0; i < sz; ++i) ++mid;

  if (*mid >= min && *mid <= max)
    return mid;
  else if (size <= 0)
    return this->end();
  else if (max < *mid)
    return find(min, max, sz, begin, ++mid);
  else
    return find(min, max,  size - sz - 1, ++mid, end);
}

template<typename T>
typename List<T>::iterator List<T>
::getSortedPos(const T &val, size_t size, iterator begin, iterator end) {
  auto sz = size / 2;
  iterator mid = begin;
  for (int i = 0; i < sz; ++i) ++mid;

  if (size <= 0)
    return mid;
  else if (val < *mid)
    return getSortedPos(val, sz, begin, ++mid);
  else
    return getSortedPos(val, size - sz - 1, ++mid, end);
}
