#pragma once

#include <list>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream> //debug only
#include <limits>
using namespace std;


namespace sorting {
  template <typename T>
  T DefaultGetter(T &val) {
    return val;
  }


  template <typename iterator>
  void std_sort(iterator beg, iterator end) {
    std::sort(beg, end);
  }

  template <typename iterator, typename T = typeof(*iterator())>
  void radix_sort(iterator beg, iterator end) {
    T m = *max_element(beg, end);

    for (T exp = 1; m/exp > 0; exp *= 10) {
      vector<T> output(end - beg);
      array<size_t, 10> count = {0};

      for (iterator i = beg; i != end; ++i)
        count[(*i / exp) % 10]++;

      for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

      for (iterator i = end - 1; i >= beg; --i) {
        output[count[ (*i/exp)%10 ] - 1] = *i;
        count[ (*i/exp)%10 ]--;
      }

      for (iterator i = beg; i != end; ++i)
        *i = output[i - beg];
    }
  }

  template <typename iterator, typename T = typeof(*iterator())>
  void counting_sort(iterator beg, iterator end,
              T min = numeric_limits<T>::min(),
              T max = numeric_limits<T>::max(),
              function<T(T&)> getter = DefaultGetter<T>) {

    if (end > beg) {
      if (min == numeric_limits<T>::min()) min = *std::min_element(beg, end);
      if (max == numeric_limits<T>::max()) max = *std::max_element(beg, end);

      vector<list<T>> lists(max - min + 1);

      for (iterator i = beg; i != end; ++i)
        lists[getter(*i) - min].push_back(*i);

      auto it = beg;
      for (int i = min; i <= max; ++i)
        for (auto a : lists[i - min])
          *it++ = a;
    }
  }
}