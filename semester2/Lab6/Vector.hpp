#pragma once

#include "Container.hpp"
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template<typename T>
class Vector : public SortedContainer<T> {
public:
  class iterator;

  Vector(const Vector<T> &val);
  Vector<T> &operator=(const Vector<T> &val);

  Vector(Vector<T> &&val) noexcept ;
  Vector<T> &operator=(Vector<T> &&val) noexcept ;

  Vector() : ptr(new T[0]), sz(0), cap(0) {};
  explicit Vector(size_t size, const T &value = T());
  Vector(const std::initializer_list<T> &ls);

  virtual ~Vector();

  T &front() override;
  T &back() override;
  T &operator[](size_t index);

  const T &front() const override;
  const T &back() const override;
  const T &operator[](size_t index) const;

  [[nodiscard]] size_t size() const override;
  void clear() override;

  void insert(const T &val) override;
  void remove(const T &val) override;

  [[nodiscard]] size_t capacity() const;
  iterator begin() const;
  iterator end() const;
  void resize(size_t size);
  void reserve(size_t new_cap);

  void print() const;

  friend std::ostream &operator<<(std::ostream &out, const Vector &val) {
    if (val.sz) {
      out << '{';
      for (size_t i = 0; i < val.sz - 1; ++i) {
        out << val.ptr[i] << ", ";
      }
      out << val.ptr[val.sz - 1] << "}";
    }
    else {
      out << "{}";
    }
    return out;
  }

private:
  size_t sz, cap;
  T *ptr;

  static void copy(T *p1, T const *p2, size_t size);
  static void copy(T *p1, T const *p2, size_t s1, size_t s2, size_t size);
  void realloc();
  size_t getSortedPos(const T &val, size_t begin, size_t end);
  void erase(size_t index);
};

template<typename T>
class Vector<T>::iterator :
        public std::iterator<std::random_access_iterator_tag, T> {

public:
  const Vector<T> *vec;
  size_t index;

  iterator() : index(0) {};

  explicit iterator(size_t index, const Vector<T> *vec) : index(index),
                                                          vec(vec) {};

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
    return iterator(index - 1, vec);
  }

  iterator operator--(int) {
    --index;
    return iterator(index + 1, vec);
  }

  T *operator->() const {
    return vec->ptr + index;
  }

  T &operator*() const {
    return vec->ptr[index];
  };

  friend bool operator<(const iterator &it1, const iterator &it2) {
    return it1.index < it2.index;
  }
  friend bool operator>(const iterator &it1, const iterator &it2) {
    return it1.index > it2.index;
  }
  friend bool operator<=(const iterator &it1, const iterator &it2) {
    return it1.index <= it2.index;
  }
  friend bool operator>=(const iterator &it1, const iterator &it2) {
    return it1.index >= it2.index;
  }
  friend bool operator==(const iterator &it1, const iterator &it2) {
    return it1.index == it2.index;
  }
  friend bool operator!=(const iterator &it1, const iterator &it2) {
    return it1.index != it2.index;
  }

  std::ptrdiff_t operator-(const iterator & val) const {
    return index - val.index;
  }

  iterator &operator+=(size_t val) {
    index += val;
    return *this;
  }

  iterator &operator-=(size_t val) {
    index -= val;
    return *this;
  }

  friend iterator operator+(const iterator &it, size_t val) {
    return iterator(it.index + val, it.vec);
  }

  friend iterator operator+(size_t val, const iterator &it) {
    return iterator(it.index + val, it.vec);
  }

  friend iterator operator-(const iterator &it, size_t val) {
    return iterator(it.index - val, it.vec);
  }

  T &operator[](size_t index) const {
    return vec->ptr[index];
  }
};


template<typename T>
void Vector<T>::copy(T *p1, T const *p2, size_t s1, size_t s2, size_t size) {
  for (int i = 0; i < size; ++i)
    p1[s1 + i] = p2[s2 + i];
}

template<typename T>
void Vector<T>::copy(T *p1, T const *p2, size_t size) {
  for (int i = 0; i < size; ++i)
    p1[i] = p2[i];
}


template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &val) {
  delete[] ptr;
  sz = val.sz;
  cap = val.cap;
  ptr = new T[cap];
  copy(ptr, val.ptr, sz);
  return *this;
}

template<typename T>
void Vector<T>::reserve(size_t new_cap) {
  if (new_cap > cap) {
    cap = new_cap;
    realloc();
  }
}

template<typename T>
void Vector<T>::resize(size_t size) {
  sz = size;
  if (size > cap) {
    realloc();
  }
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() const {
  return iterator(0, this);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() const {
  return iterator(sz, this);
}

template<typename T>
T &Vector<T>::front() {
  return ptr[0];
};

template<typename T>
T &Vector<T>::back() {
  return ptr[sz - 1];
};

template<typename T>
const T &Vector<T>::front() const {
  return ptr[0];
};

template<typename T>
const T &Vector<T>::back() const {
  return ptr[sz - 1];
};

template<typename T>
size_t Vector<T>::size() const {
  return sz;
}

template<typename T>
size_t Vector<T>::capacity() const {
  return cap;
};

template<typename T>
void Vector<T>::clear() {
  delete[] ptr;
  sz = 0;
  cap = 0;
  ptr = new T[0];
}

template<typename T>
Vector<T>::Vector(const Vector<T> &val) : sz(val.sz), cap(val.cap) {
  ptr = new T[cap];
  copy(ptr, val.ptr, sz);
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> &ls)
        : sz(ls.size()), cap(ls.size()), ptr(new T[ls.size()]) {
  int i = 0;
  for (auto a : ls) {
    ptr[i++] = a;
  }
}

template<typename T>
Vector<T>::~Vector() {
  delete[] ptr;
}

template<typename T>
void Vector<T>::realloc() {
  auto tmp = ptr;
  ptr = new T[cap];
  copy(ptr, tmp, sz);
  delete[] tmp;
}

template<typename T>
Vector<T>::Vector(size_t size, const T &value) : sz(size), cap(size) {
  ptr = new T[cap];
  for (int i = 0; i < sz; ++i) {
    ptr[i] = value;
  }
}

template<typename T>
void Vector<T>::print() const {
  std::cout << *this << std::endl;
}

template<typename T>
void Vector<T>::erase(size_t index) {
  --sz;
  for (int i = index; i < sz; ++i) {
    ptr[i] = ptr[i+1];
  }
}

template<typename T>
Vector<T>::Vector(Vector<T> &&val) noexcept :
sz(val.sz), cap(val.cap), ptr(val.ptr){
  val.ptr = new T[0];
  val.sz = 0;
  val.cap = 0;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&val) noexcept {
  ptr = val.ptr;
  cap = val.cap;
  sz = val.sz;
  val.ptr = new T[0];
  val.sz = 0;
  val.cap = 0;
}

template<typename T>
void Vector<T>::insert(const T &val) {
  if (sz + 1 > cap) {
    cap = (sz + 1) * 2;
    realloc();
  }

  auto pos = getSortedPos(val, 0, size());
  std::copy_n(ptr + pos, sz - pos, ptr + pos + 1);
  ptr[pos] = val;
  ++sz;
}

template<typename T>
size_t Vector<T>::getSortedPos(const T &val, size_t beg, size_t end) {
  auto mid = beg + (end - beg) / 2;

  if (end - beg <= 0)
    return mid;
  else if (val < ptr[mid])
    return getSortedPos(val, beg, mid);
  else
    return getSortedPos(val, mid + 1, end);
}

template<typename T>
T &Vector<T>::operator[](size_t index) {
  return ptr[index];
};

template<typename T>
const T &Vector<T>::operator[](size_t index) const {
  return ptr[index];
}

template<typename T>
void Vector<T>::remove(const T &val) {

};

