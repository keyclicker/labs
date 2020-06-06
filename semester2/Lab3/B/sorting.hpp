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

  template <typename iterator>
  void std_stable_sort(iterator beg, iterator end) {
    std::stable_sort(beg, end);
  }

  template <typename iterator, typename Int = int, typename T = typeof(*iterator())>
  void radix_sort(iterator beg, iterator end,
          function<Int(T&)> getter = DefaultGetter<T>) {

    Int m = getter(*max_element(beg, end,
            [getter](T a, T b) {return getter(a) < getter(b); }));

    for (Int exp = 1; m/exp > 0; exp *= 10) {
      vector<T> output(end - beg);
      array<size_t, 10> count = {0};

      for (iterator i = beg; i != end; ++i)
        count[(getter(*i) / exp) % 10]++;

      for (Int i = 1; i < 10; i++)
        count[i] += count[i - 1];

      for (iterator i = end - 1; i >= beg; --i) {
        output[count[ (getter(*i)/exp)%10 ] - 1] = *i;
        count[ (getter(*i)/exp)%10 ]--;
      }

      for (iterator i = beg; i != end; ++i)
        *i = output[i - beg];
    }
  }

  template <typename iterator, typename Int = int, typename T = typeof(*iterator())>
  void counting_sort(iterator beg, iterator end,
              int min = numeric_limits<T>::min(),
              int max = numeric_limits<T>::max(),
              function<Int(T&)> getter = DefaultGetter<T>) {

    if (end > beg) {
      if (min == numeric_limits<Int>::min())
        min = getter(*std::min_element(beg, end,
                [getter](T a, T b) {return getter(a) < getter(b); }));
      if (max == numeric_limits<Int>::max())
        max = getter(*std::max_element(beg, end,
                [getter](T a, T b) {return getter(a) < getter(b); }));

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
