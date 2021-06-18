#include <thread>
#include <future>

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