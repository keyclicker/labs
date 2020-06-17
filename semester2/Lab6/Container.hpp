#pragma once
#include <cstddef>
#include <initializer_list>
#include <iterator>

template <typename T>
class SortedContainer {
public:
  SortedContainer() = default;
  virtual ~SortedContainer() = default;

  virtual T front() const = 0;
  virtual T back() const = 0;

  [[nodiscard]]
  virtual size_t size() const = 0;

  virtual void insert(const T &val) = 0;
  virtual void remove(const T &val) = 0;
  virtual void clear() = 0;
};