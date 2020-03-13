#pragma once
#include "Container.hpp"
#include <initializer_list>

template <typename T>
class Vector : public DynamicContainer<T> {
private:
  size_t sz, cap;
  T *ptr;

  static void copy(T *p1, T const *p2, size_t size) {
    for (int i = 0; i < size; ++i)
      p1[i] = p2[i];
  }

  static void copy(T *p1, T const *p2, size_t s1, size_t s2, size_t size) {
    for (int i = 0; i < size; ++i)
      p1[s1 + i] = p2[s2 + i];
  }

  void realloc() {
    auto tmp = ptr;
    ptr = new T[cap];
    copy(ptr, tmp, sz);
    delete[] tmp;
  }

public:
  class iterator;

  Vector() : sz(0), cap(0) {};
  explicit Vector(size_t cap) : sz(0), cap(cap) {
    ptr = new T[cap];
  }

  Vector(const std::initializer_list<T> &ls)
  : sz(ls.size()), cap(ls.size()), ptr(new T[ls.size()]) {
    int i = 0;
    for (auto a : ls) {
      ptr[i++] = a;
    }
  };

  Vector(const Vector<T> &val) : sz(val.sz), cap(val.cap) {
    ptr = new T[cap];
    copy(ptr, val.ptr, sz);
  }

  Vector<T> operator=(const Vector<T> &val) {
    delete[] ptr;
    sz = val.sz;
    cap = val.cap;
    ptr = new T[cap];
    copy(ptr, val.ptr, sz);
    return *this;
  }

  void reserve(size_t new_cap) {
    if (new_cap > cap) {
      cap = new_cap;
      realloc();
    }
  }

  void resize(size_t size) {
    sz = size;
    if (size > cap) {
      realloc(ptr, cap, sz);
    }
  }

  void push_back(const T &val) override {
    if (sz + 1 > cap) {
      cap = (sz + 1) * 2;
      realloc();
    }
    ptr[sz] = val;
    ++sz;
  }

  void push_front(const T &val) override  { //todo optimization
    if (sz + 1 > cap) {
      cap = (sz + 1) * 2;
    }

    auto tmp = ptr;
    ptr = new T[cap];
    copy(ptr, tmp, 1, 0, sz);
    delete[] tmp;

    ptr[0] = val;
    ++sz;
  }

  T &operator[](size_t index) override {
    return ptr[index];
  };

  const T &operator[](size_t index) const override {
    return ptr[index];
  };

  iterator begin() const {
    return iterator(0, this);
  }

  iterator end() const {
    return iterator(sz, this);
  }

  T &front() override {
    return ptr[0];
  };

  T &back() override {
    return ptr[sz-1];
  };

  const T &front() const override {
    return ptr[0];
  };

  const T &back() const override {
    return ptr[sz-1];
  };

  size_t size() const override {
    return sz;
  }

  size_t capacity() const {
    return cap;
  };

  void insert(size_t index, const T &val) override { //todo optimization
    if (sz + 1 > cap) {
      cap = (sz + 1) * 2;
    }

    auto tmp = ptr;
    ptr = new T[cap];
    copy(ptr, tmp, index+1, index, sz-index);
    copy(ptr, tmp, 0, 0, index);
    delete[] tmp;

    ptr[index] = val;
    ++sz;
  }

  void assign() override { //todo assign

  }

  void clear() override {
    delete[] ptr;
    sz = 0;
    cap = 0;
  }

  friend std::ostream& operator<<(std::ostream& out, const Vector &val) {
    out << '{';
    for (size_t i = 0; i < val.sz-1; ++i) {
      out << val.ptr[i] << ", ";
    }
    out << val.ptr[val.sz-1] << "}";
    return out;
  }
};

template<typename T>
class Vector<T>::iterator {
  const Vector<T> *vec; //todo check
  size_t index;
public:
  iterator() : index(0) {};
  explicit iterator(size_t index, const Vector<T> *vec) : index(index), vec(vec) {};

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
  T *operator->() const {
    return vec->ptr+index;
  }
  T &operator*() const{
    return vec->ptr[index];
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
    return vec->ptr[index];
  }
};





