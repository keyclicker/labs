#include "sorting.hpp"

#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

#include <benchmark/benchmark.h>


random_device rd;
default_random_engine re(rd());
uniform_real_distribution<double> drand(-100, 100);

#define SORTBENCH(name, algo) \
void name(benchmark::State& state) { \
  std::vector<double> a;\
  for (auto _ : state) { \
    state.PauseTiming(); \
      a.clear();\
      for (int i = 0; i < state.range(); ++i)\
        a.emplace_back(drand(re));\
    state.ResumeTiming(); \
    algo(a.begin(), a.end());\
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(2, 256) \


SORTBENCH(RandomSelectionSort, sorting::selection);
SORTBENCH(RandomQuickSort, sorting::quicksort);
SORTBENCH(RandomMergeSort, sorting::merge);
SORTBENCH(RandomCombinedSort10, sorting::combined);
SORTBENCH(RandomStdSort, sorting::std_sort);


#define ALMOSTBENCH(name, algo) \
void name(benchmark::State& state) { \
  std::vector<double> a;\
  for (auto _ : state) { \
    state.PauseTiming(); \
      a.clear();\
      for (int i = 0; i < state.range(); ++i)\
        a.emplace_back(drand(re));\
      sorting::std_sort(a.begin(), a.end());\
      a[rand() % state.range()] = drand(re); \
    state.ResumeTiming(); \
    algo(a.begin(), a.end());\
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(2, 256) \

ALMOSTBENCH(AlmostSortedSelectionSort, sorting::selection);
ALMOSTBENCH(AlmostSortedQuickSort, sorting::quicksort);
ALMOSTBENCH(AlmostSortedMergeSort, sorting::merge);
ALMOSTBENCH(AlmostSortedCombinedSort10, sorting::combined);
ALMOSTBENCH(AlmostSortedStdSort, sorting::std_sort);


#define RALMOSTBENCH(name, algo) \
void name(benchmark::State& state) { \
  std::vector<double> a;\
  for (auto _ : state) { \
    state.PauseTiming(); \
      a.clear();\
      for (int i = 0; i < state.range(); ++i)\
        a.emplace_back(drand(re));\
      sorting::std_sort(a.begin(), a.end());\
      reverse(a.begin(), a.end());\
      a[rand() % state.range()] = drand(re); \
    state.ResumeTiming(); \
    algo(a.begin(), a.end());\
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(2, 256) \


RALMOSTBENCH(ReversedAlmostSortedSelectionSort, sorting::selection);
RALMOSTBENCH(ReversedAlmostSortedQuickSort, sorting::quicksort);
RALMOSTBENCH(ReversedAlmostSortedMergeSort, sorting::merge);
RALMOSTBENCH(ReversedAlmostSortedCombinedSort10, sorting::combined);
RALMOSTBENCH(ReversedAlmostSortedStdSort, sorting::std_sort);


BENCHMARK_MAIN();

