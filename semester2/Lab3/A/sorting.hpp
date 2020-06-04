#pragma once

#include <vector>
#include <iostream> //debug only

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
      auto pivot = *(beg + (end - beg) / 2);
      iterator i = beg, j = end;

      while (i <= j) {
        while (*i < pivot) ++i;
        while (*j > pivot) --j;

        if (i <= j) std::swap(*(i++), *(j--));
      };

      quicksort(beg, j);
      quicksort(i, end);
    }
  }

  template <typename iterator>
  void merge(iterator beg, iterator end) {
    if (beg < end) {
      iterator mid = beg + (end - beg - 1) / 2;

      merge(beg, mid);
      merge(mid + 1, end);

      using T = typeof(*beg);

      int n1 = mid - beg + 1;
      int n2 = end - mid - 1;

      std::vector<T> L(n1), R(n2);

      for (int i = 0; i < n1; i++)
        L[i] = *(beg + i);
      for (int j = 0; j < n2; j++)
        R[j] = *(mid + j + 1);

      int i = 0;
      int j = 0;
      iterator k = beg;
      while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
          *k = L[i];
          i++;
        }
        else {
          *k = R[j];
          j++;
        }
        k++;
      }

      while (i < n1) {
        *k = L[i];
        i++;
        k++;
      }

      while (j < n2) {
        *k = R[j];
        j++;
        k++;
      }
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