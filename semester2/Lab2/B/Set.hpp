#pragma once

#include "../A/List.hpp"

template <typename T>
class Set {
private:
  List<T> list;

public:
  Set() = default;
  Set(std::initializer_list<T> ls) : list(ls) {}

  Set(const Set &val) : list(val.list) {}
  Set(Set &&val) : list(std::move(val.list)) {}

  Set &operator=(const Set &val) {
    list = val.list;
    return *this;
  }
  Set &operator=(Set &&val) noexcept {
    list = std::move(val.list);
    return *this;
  }

  auto begin() const{
    return list.begin();
  }

  auto end() const{
    return list.begin();
  }

  size_t size() {
    return list.size();
  }

  void insert(const T &val) {
    list.push_back(val);
  }

  void erase(const T &val) {
    for (auto i = list.begin(); i != list.end(); ++i) {
      if (*i == val) list.erase(i);
    }
  }

  bool contains(const T &val) const {
    for (auto i = list.begin(); i != list.end(); ++i) {
      if (*i == val) return true;
    }
    return false;
  }

  Set &operator+=(const Set &val) {
    for (auto a : val.list) {
      list.push_back(a);
    }
    return *this;
  }
  Set &operator-=(const Set &val) {
    for (auto i = val.list.begin(); i != val.list.end(); ++i) {
      erase(*i);
    }
    return *this;
  }

  Set operator+(const Set &val) const {
    Set set = *this;
    set += val;
    return set;
  }
  Set operator-(const Set &val) const {
    Set set = *this;
    set -= val;
    return set;
  }

  Set operator^(const Set &val) const {
    Set set;
    for (auto i = list.begin(); i != list.end(); ++i) {
      for (auto j = val.list.begin(); j != val.list.end(); ++j) {
        if (*i == *j) set.insert(*i);
      }
    }
    return set;
  }

  friend std::ostream &operator<<(std::ostream &out, const Set &val) {
    out << val.list;
    return out;
  }
};