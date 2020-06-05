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
->Range(2, 2048*8) \


SORTBENCH(stdSort, sorting::std_sort);
SORTBENCH(stdStableSort, sorting::std_stable_sort);
SORTBENCH(RadixSort, sorting::radix_sort);
SORTBENCH(CountingSort, sorting::counting_sort);

BENCHMARK_MAIN();