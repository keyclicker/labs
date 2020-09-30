#pragma once

#include <vector>
#include <algorithm>

namespace sorting {

  template <typename iterator>
  void selection(iterator beg, iterator end) {
    for (auto i = beg; i != end; ++i) {
      iterator min = i;
      for (auto j = i; j != end; ++j) {
        if (*j < *min) min = j;
      }
      std::swap(*i, *min);
    }
  }

  template <typename iterator>
  void quicksort(iterator beg, iterator end) {
    if (end > beg) {
      auto pivot = *(beg + (end - beg - 1) / 2);
      iterator i = beg, j = end - 1;

      while (i <= j) {
        while (*i < pivot) ++i;
        while (*j > pivot) --j;

        if (i <= j) std::swap(*(i++), *(j--));
      };

      quicksort(beg, j + 1);
      quicksort(i, end);
    }
  }

  template <typename iterator>
  void merge(iterator beg, iterator end) {
    if (end - 1 > beg) {
      auto mid = beg + (end - beg) / 2;
      merge(beg, mid);
      merge(mid, end);

      std::vector<typeof(*beg)> v;
      v.reserve(end - beg);

      iterator l = beg, r = mid;
      while (l < mid && r < end) {
        v.push_back((*l <= *r) ? *l++ : *r++);
      }

      v.insert(v.end(), l, mid);
      v.insert(v.end(), r, end);

      move(v.begin(), v.end(), beg);
    }
  }

  //size < threshold - selection sort
  //size > threshold - quick sort
  template <typename iterator>
  void combined(iterator beg, iterator end, size_t threshold = 10) {
    if (end - beg > threshold) {
      auto pivot = *(beg + (end - beg - 1) / 2);
      iterator i = beg, j = end - 1;

      while (i <= j) {
        while (*i < pivot) ++i;
        while (*j > pivot) --j;

        if (i <= j) std::swap(*(i++), *(j--));
      };

      combined(beg, j + 1);
      combined(i, end);
    }
    else if (end > beg) {
      sorting::selection(beg, end);
    }
  }

  template <typename iterator>
  void std_sort(iterator beg, iterator end) {
    std::sort(beg, end);
  }
}