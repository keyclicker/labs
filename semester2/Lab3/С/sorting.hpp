#pragma once

#include <future>
#include <thread>
#include <vector>
#include <algorithm>
#include <iostream> // debug only
#include <iomanip>

namespace sorting {
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
  void quicksort_async(iterator beg, iterator end) {
    if (end > beg) {
      auto pivot = *(beg + (end - beg - 1) / 2);
      iterator i = beg, j = end - 1;

      while (i <= j) {
        while (*i < pivot) ++i;
        while (*j > pivot) --j;

        if (i <= j) std::swap(*(i++), *(j--));
      };

      if (end - beg > 2048) {
        auto f1 = std::async(std::launch::async, quicksort_async<iterator>, beg, j + 1);
        auto f2 = std::async(std::launch::async, quicksort_async<iterator>, i, end);
        f1.wait(), f2.wait();
      }
      else {
        quicksort(beg, j + 1);
        quicksort(i, end);
      }

    }
  }

  template <typename iterator>
  void merge(iterator beg, iterator end) {
    if (end - 1 > beg) {
      auto mid = beg + (end - beg) / 2;
      merge(beg, mid);
      merge(mid, end);

      std::inplace_merge(beg, mid, end);
    }
  }

  template <typename iterator>
  void merge_async(iterator beg, iterator end) {
    if (end - 1 > beg) {
      auto mid = beg + (end - beg) / 2;

      if (end - beg > 2048) {
        auto f1 = std::async(std::launch::async, merge<iterator>, beg, mid);
        auto f2 = std::async(std::launch::async, merge<iterator>, mid, end);
        f1.wait(), f2.wait();
      }
      else {
        merge(beg, mid);
        merge(mid, end);
      }

      std::inplace_merge(beg, mid, end);
    }
  }


  template <typename iterator>
  void insertion(iterator beg, iterator end) {
    for (iterator i = beg + 1; i <= end; i++) {
      auto temp = *i;
      iterator j = i - 1;
      while (j >= beg && *j > temp) {
        *(j+1) = *(j);
        j--;
      }
      *(j+1) = temp;
    }
  }

  template <typename iterator>
  void timsort(iterator beg, iterator end) {
    static constexpr auto thr = 8;

    for (iterator i = beg; i < end; i += thr)
      insertion(i, beg + std::min((i - beg + thr - 1), (end - beg - 1)));

    for (int size = thr; size < end - beg; size = 2*size) {
      for (iterator left = beg; left < end; left += 2*size) {
        iterator mid = std::min(left + size, end - 1);
        iterator right = std::min((left + 2*size), (end));

        std::inplace_merge(left, mid, right);
      }
    }
  }
}