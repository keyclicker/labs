#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

#include <benchmark/benchmark.h>

#include "Multisort.hpp"
#include "Graph.hpp"



void LinierFloyd(benchmark::State& state) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> weight(0.1, 10.0);

  for (auto _ : state) {
    state.PauseTiming();
    Graph<double> graph(state.range());

    std::uniform_int_distribution<int>
        rec(0, state.range() * state.range()),
        randEdge(0, state.range() - 1), isDir(0, 1);

    for (int i = 0; i < rec(mt); ++i) {
      if (isDir(mt))
        graph.addDirEdge(randEdge(mt), randEdge(mt), weight(mt));
      else
        graph.addUndirEdge(randEdge(mt), randEdge(mt), weight(mt));
    }
    state.ResumeTiming();

    graph.floydWarshall();
  };
}
BENCHMARK(LinierFloyd)
->Unit(benchmark::TimeUnit::kMicrosecond)
->RangeMultiplier(2)
->Range(2, 1024);


void MultiFloyd(benchmark::State& state) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> weight(0.1, 10.0);

  for (auto _ : state) {
    state.PauseTiming();
    Graph<double> graph(state.range());

    std::uniform_int_distribution<int>
        rec(0, state.range() * state.range()),
        randEdge(0, state.range() - 1), isDir(0, 1);

    for (int i = 0; i < rec(mt); ++i) {
      if (isDir(mt))
        graph.addDirEdge(randEdge(mt), randEdge(mt), weight(mt));
      else
        graph.addUndirEdge(randEdge(mt), randEdge(mt), weight(mt));
    }
    state.ResumeTiming();

    graph.floydWarshallMulti();
  };
}
BENCHMARK(MultiFloyd)
    ->Unit(benchmark::TimeUnit::kMicrosecond)
    ->RangeMultiplier(2)
    ->Range(2, 1024);


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
->Range(2, 16384) \



SORTBENCH(AsyncQuickSort, quicksort_async);
SORTBENCH(QuickSort, quicksort);
SORTBENCH(AsyncMergeSort, merge_async);
SORTBENCH(MergeSort, merge);
SORTBENCH(stdSort, std::sort);

BENCHMARK_MAIN();