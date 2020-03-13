#pragma once
#include "Container.hpp"
#include <initializer_list>

template <typename T, size_t sz>
class Array : public StaticContainer<T> {
private:
  T arr[sz];

public:
  class iterator;

  Array() = default;
  virtual ~Array() = default;

  Array(const std::initializer_list<T> &ls) {
    int i = 0;
    for (auto a : ls) {
      arr[i++] = a;
    }
  };

  T &operator[](size_t index) override {
    return arr[index];
  };

  const T &operator[](size_t index) const override {
    return arr[index];
  };

  iterator begin() {
    return iterator(0, this);
  }
  iterator end() {
    return iterator(sz, this);
  }

  T &front() override {
    return arr[0];
  };

  T &back() override {
    return arr[sz-1];
  };

  const T &front() const override {
    return arr[0];
  };

  const T &back() const override {
    return arr[sz-1];
  };

  size_t size() const override {
    return sz;
  }
};

template<typename T, size_t sz>
class Array<T, sz>::iterator {
  Array<T, sz> *vec; //todo check
  size_t index;

public:
  iterator() : index(0) {};
  explicit iterator(size_t index, Array<T, sz> *vec) : index(index), vec(vec) {};

  iterator(const iterator &val) = default;

  iterator &operator++() {
    ++index;
    return *this;
  }
  iterator &operator--() {
    --index;
    return *this;
  }
  iterator operator++(int) {
    ++index;
    return iterator(index-1, vec);
  }
  iterator operator--(int) {
    --index;
    return iterator(index+1, vec);
  }

  const T *operator->() const {
    return vec->arr+index;
  }
  T &operator*() { //todo fix
    return vec->arr[index];
  };

  friend bool operator<(const iterator& it1, const iterator& it2) {
    return it1.index < it2.index;
  }
  friend bool operator>(const iterator& it1, const iterator& it2) {
    return it1.index > it2.index;
  }
  friend bool operator<=(const iterator& it1, const iterator& it2) {
    return it1.index <= it2.index;
  }
  friend bool operator>=(const iterator& it1, const iterator& it2) {
    return it1.index >= it2.index;
  }
  friend bool operator==(const iterator& it1, const iterator& it2) {
    return it1.index == it2.index;
  }
  friend bool operator!=(const iterator& it1, const iterator& it2) {
    return it1.index != it2.index;
  }

  iterator& operator+=(size_t val) {
    index += val;
    return *this;
  }
  iterator& operator-=(size_t val) {
    index -= val;
    return *this;
  }

  friend iterator operator+(const iterator& it, size_t val) {
    return iterator(it.index + val, it.vec);
  }
  friend iterator operator+(size_t val, const iterator& it) {
    return iterator(it.index + val, it.vec);
  }
  friend iterator operator-(const iterator& it, size_t val) {
    return iterator(it.index - val, it.vec);
  }

  T &operator[](size_t index) const {
    return vec->arr[index];
  }
};





