#pragma once

#include <vector>

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
    if (beg < end) {
      auto pivot = beg + (end - beg) / 2;
      iterator i = beg, j = end - 1;

      while (i < j) {
        while (*i < *pivot) ++i;
        while (*j > *pivot) --j;

        if (i < j)
          std::swap(*(i++), *(j--));
      }

      quicksort(beg, j - 1);
      quicksort(j + 1, end);
    }
  }

  template <typename iterator>
  void merge(iterator beg, iterator mid, iterator end)
  {
    int i, j, k;
    int n1 = mid - beg + 1;
    int n2 =  end - beg;

    /* create temp arrays */
    std::vector<> L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
      L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
      R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
      if (L[i] <= R[j])
      {
        arr[k] = L[i];
        i++;
      }
      else
      {
        arr[k] = R[j];
        j++;
      }
      k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
      arr[k] = L[i];
      i++;
      k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
      arr[k] = R[j];
      j++;
      k++;
    }
  }

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
  template <typename iterator>
  void mergeSort(iterator beg, iterator end)
  {
    if (beg < end)
    {
      // Same as (l+r)/2, but avoids overflow for
      // large l and h
      iterator mid = beg + (end - beg) / 2;

      // Sort first and second halves
      mergeSort(beg, mid);
      mergeSort(mid + 1, end);

      merge(beg, mid, end);
    }
  }
}