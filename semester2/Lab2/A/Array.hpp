#pragma once

#include "Container.hpp"
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T, size_t sz>
class Array : public StaticContainer<T> {
private:
  T arr[sz];

  static void copy(T *p1, T const *p2, size_t size);

public:
  class iterator;

  Array() = default;
  virtual ~Array() = default;

  Array(const std::initializer_list<T> &ls);
  Array(const Array<T, sz> &val);
  Array<T, sz> &operator=(const Array<T, sz> &val);

  T &front() override;
  T &back() override;
  T &operator[](size_t index) override;
  T &at(size_t index) override;

  const T &front() const override;
  const T &back() const override;
  const T &operator[](size_t index) const  override;
  const T &at(size_t index) const override;

  size_t size() const override;
  void print() const override;

  iterator begin();
  iterator end();

  friend std::ostream& operator<<(std::ostream& out, const Array<T, sz> &val) {
    out << '{';
    for (size_t i = 0; i < sz-1; ++i) {
      out << val.arr[i] << ", ";
    }
    out << val.arr[sz-1] << "}";
    return out;
  }
};

template<typename T, size_t sz>
class Array<T, sz>::iterator {
  Array<T, sz> *vec;
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
  T &operator*() {
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

template<typename T, size_t sz>
T &Array<T, sz>::operator[](size_t index) {
return arr[index];
};

template<typename T, size_t sz>
const T &Array<T, sz>::operator[](size_t index) const {
return arr[index];
};

template<typename T, size_t sz>
typename Array<T, sz>::iterator Array<T, sz>::begin() {
  return iterator(0, this);
}

template<typename T, size_t sz>
typename Array<T, sz>::iterator Array<T, sz>::end() {
  return iterator(sz, this);
}

template<typename T, size_t sz>
T &Array<T, sz>::front() {
return arr[0];
};

template<typename T, size_t sz>
T &Array<T, sz>::back() {
return arr[sz-1];
};

template<typename T, size_t sz>
const T &Array<T, sz>::front() const {
return arr[0];
};

template<typename T, size_t sz>
const T &Array<T, sz>::back() const {
return arr[sz-1];
};

template<typename T, size_t sz>
size_t Array<T, sz>::size() const {
return sz;
}

template<typename T, size_t sz>
Array<T, sz>::Array(const std::initializer_list<T> &ls) {
  int i = 0;
  for (auto a : ls) {
    arr[i++] = a;
  }
}

template<typename T, size_t sz>
Array<T, sz> &Array<T, sz>::operator=(const Array<T, sz> &val) {
  copy(arr, val.arr, sz);
  return *this;
}

template<typename T, size_t sz>
Array<T, sz>::Array(const Array<T, sz> &val) {
  copy(arr, val.arr, sz);
}

template<typename T, size_t sz>
void Array<T, sz>::copy(T *p1, T const *p2, size_t size) {
  for (int i = 0; i < size; ++i)
    p1[i] = p2[i];
}

template<typename T, size_t sz>
T &Array<T, sz>::at(size_t index) {
  if (index >= sz) throw std::out_of_range ("index >= size, index = "
    + std::to_string(index) + " size = " + std::to_string(sz));
  return operator[](index);
}

template<typename T, size_t sz>
const T &Array<T, sz>::at(size_t index) const {
  if (index >= sz) throw std::out_of_range ("index >= size, index = "
    + std::to_string(index) + " size = " + std::to_string(sz));
  return operator[](index);
}

template<typename T, size_t sz>
void Array<T, sz>::print() const {
  std::cout << *this << std::endl;
}






