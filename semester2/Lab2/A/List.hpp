#pragma once

#include "Container.hpp"
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T>
class List : public DynamicContainer<T> {
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

public:
  class iterator;
  
  List() = default;
  List(const List &ls);
  List<T> &operator=(const List &ls);

  List(std::initializer_list<T> list);
  explicit List(size_t size, const T &value = T());

  virtual ~List();

  T &front() override;
  T &back() override;
  T &operator[](size_t index) override;
  T &at(size_t index) override;

  const T &front() const override;
  const T &back() const override;
  const T &operator[](size_t index) const override;
  const T &at(size_t index) const override;

  size_t size() const override;
  void print() const override;

  void push_front(const T &val) override;
  void push_back(const T &val) override;
  void insert(size_t index, const T &val) override;
  void assign() override {}
  void erase(size_t index) override;
  void clear() override;

  iterator begin() const;
  iterator end() const;

  friend std::ostream& operator<<(std::ostream& out, const List &val) {
    if (val.sz) {
      out << '{';
      for (auto i = val.begin(); i != val.end() - 1; ++i) {
        out << *i << ", ";
      }
      out << val.back() << "}";
    }
    else {
      out << "{}";
    }
    return out;
  }
};

template<typename T>
class List<T>::iterator :
        public std::iterator<std::bidirectional_iterator_tag, T> {

  Node *node;

public:
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

  iterator &operator+=(size_t val) {
    if (val > 0) {
      for (int i = 0; i < val; ++i)
        this->operator++();
    }
    else {
      for (int i = 0; i < val; ++i)
        this->operator--();
    }
    return *this;
  }

  iterator &operator-=(size_t val) {
    if (val > 0) {
      for (int i = 0; i < val; ++i)
        this->operator--();
    }
    else {
      for (int i = 0; i < val; ++i)
        this->operator++();
    }
    return *this;
  }

  friend iterator operator+(iterator it, size_t val) {
    return it += val;
  }
  friend iterator operator+(size_t val, const iterator& it) {
    return it += val;
  }
  friend iterator operator-(iterator it, size_t val) {
    return it -= val;;
  }

  T &operator[](size_t index) const {
    auto ret = node;
    return ret += index;;
  }
};

template<typename T>
void List<T>::push_front(const T &val) {
  begin_ = new Node(val, nullptr, begin_);
  begin_->next->prev = begin_;
  if (!sz++) end_->prev = begin_;
}

template<typename T>
void List<T>::push_back(const T &val) {
  end_->prev = new Node(val, end_->prev, end_);
  if (end_->prev->prev) end_->prev->prev->next = end_->prev;
  if (!sz++) begin_ = end_->prev;
}

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
T &List<T>::operator[](size_t index) {
  auto a = begin_;
  for (int i = 0; i < index; ++i) a = a->next;
  return a->value;
}

template<typename T>
const T &List<T>::operator[](size_t index) const {
  auto a = begin_;
  for (int i = 0; i < index; ++i) a = a->next;
  return a->value;
}

template<typename T>
void List<T>::insert(size_t index, const T &val) {
  if (!index) {
    begin_ = new Node(val, nullptr, begin_);
  }
  else {
    auto a = begin_;
    for (int i = 0; i < index-1; ++i) a = a->next;
    a->next = new List<T>::Node(val, a, a->next);
    a->next->next->prev = a->next;
  }
  ++sz;
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
List<T>::List(std::initializer_list<T> list) {
  for (auto a : list) {
    push_back(a);
  }
}

template<typename T>
List<T>::List(const List &ls) {
  for (auto i = ls.begin_; i != ls.end_; i = i->next) {
    push_back(i->value);
  }
}

template<typename T>
List<T> &List<T>::operator=(const List &ls) {
  for (auto i = ls.begin_; i != ls.end_; i = i->next) {
    push_back(i->value);
  }
  return *this;
}

template<typename T>
T &List<T>::at(size_t index) {
  if (index >= sz) throw std::out_of_range ("index >= size, index = "
    + std::to_string(index) + " size = " + std::to_string(sz));
  return operator[](index);
}

template<typename T>
const T &List<T>::at(size_t index) const {
  if (index >= sz) throw std::out_of_range ("index >= size, index = "
    + std::to_string(index) + " size = " + std::to_string(sz));
  return operator[](index);
}

template<typename T>
List<T>::List(size_t size, const T &value) {
  for (int i = 0; i < size; ++i) {
    push_back(value);
  }
}

template<typename T>
void List<T>::print() const {
  std::cout << *this << std::endl;
}

template<typename T>
void List<T>::erase(size_t index) {
  auto i = begin_;
  if (index) {
    for (int j = 0; j < index; ++j) i = i->next;
    i->prev->next = i->next;
  }
  else {
    begin_ = begin_->next;
  }
  i->next->prev = i->prev;
  delete i;
}
