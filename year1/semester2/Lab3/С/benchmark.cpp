#include "sorting.hpp"

#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

#include <benchmark/benchmark.h>


random_device rd;
default_random_engine re(rd());
uniform_int_distribution<int> drand(0, 100);

#define SORTBENCH(name, algo) \
void name(benchmark::State& state) { \
  std::vector<int> a;\
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
->Range(2, 2048*32) \



SORTBENCH(AsyncQuickSort, sorting::quicksort_async);
SORTBENCH(QuickSort, sorting::quicksort);
SORTBENCH(AsyncMergeSort, sorting::merge_async);
SORTBENCH(MergeSort, sorting::merge);
SORTBENCH(TimSort, sorting::timsort);
SORTBENCH(stdSort, std::sort);

BENCHMARK_MAIN();