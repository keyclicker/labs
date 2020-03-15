#pragma once
#include <cstddef>
#include <initializer_list>

//TODO iterator insert
//TODO append

template <typename T>
class StaticContainer {
public:
  StaticContainer() = default;
  virtual ~StaticContainer() = default;

  virtual T &front() = 0;
  virtual T &back() = 0;
  virtual T &operator[](size_t index) = 0;
  virtual T &at(size_t index) = 0;

  virtual const T &front() const = 0;
  virtual const T &back() const = 0;
  virtual const T &operator[](size_t index) const  = 0;
  virtual const T &at(size_t index) const = 0;

  virtual size_t size() const = 0;
  virtual void print() const = 0;
};

template <typename T>
class DynamicContainer : public StaticContainer<T>{
public:
  DynamicContainer() = default;
  virtual ~DynamicContainer() = default;

  virtual void push_front(const T &val) = 0;
  virtual void push_back(const T &val) = 0;
  virtual void insert(size_t index, const T &val) = 0;
  virtual void erase(size_t index) = 0;
  virtual void assign() = 0;
  virtual void clear() = 0;
};
