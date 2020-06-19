#include "src/List.hpp"
#include "src/Vector.hpp"
#include "src/Tree.hpp"
#include "src/AVL.hpp"
#include <list>
#include <vector>

#include <benchmark/benchmark.h>
using namespace std;

template<typename T>
auto rand(T a, T b) {
  random_device rd;
  default_random_engine re(rd());
  uniform_int_distribution<T> drand(a, b);
  return drand(re);
}

#define INSERTBENCH(name, container) \
void name(benchmark::State& state) { \
  auto *c = new container<int>(); \
  for (auto _ : state) { \
    state.PauseTiming(); \
    delete c; \
    c = new container<int>(); \
    for (int i = 0; i < state.range(); ++i) \
      c->insert(rand(-10000, 10000)); \
    state.ResumeTiming(); \
      c->insert(rand(-10000, 10000)); \
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(256, 4096) \
->Iterations(500)

INSERTBENCH(ListInsert, List);
INSERTBENCH(VectorInsert, Vector);
INSERTBENCH(TreeInsert, Tree);
INSERTBENCH(AvlTreeInsert, AvlTree);

#define FINDBENCH(name, container) \
void name(benchmark::State& state) { \
  auto *c = new container<int>(); \
  for (auto _ : state) { \
    state.PauseTiming(); \
    delete c; \
    c = new container<int>(); \
    for (int i = 0; i < state.range(); ++i) \
      c->insert(rand(-10000, 10000)); \
    c->insert(42);\
    state.ResumeTiming(); \
      c->find(42); \
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(256, 4096) \
->Iterations(500)

FINDBENCH(ListFind, List);
FINDBENCH(VectorFind, Vector);
FINDBENCH(TreeFind, Tree);
FINDBENCH(AvlTreeFind, AvlTree);

#define REMOVEBENCH(name, container) \
void name(benchmark::State& state) { \
  auto *c = new container<int>(); \
  for (auto _ : state) { \
    state.PauseTiming(); \
    delete c; \
    c = new container<int>(); \
    for (int i = 0; i < state.range(); ++i) \
      c->insert(rand(-10000, 10000)); \
    c->insert(42);\
    state.ResumeTiming(); \
      c->remove(42); \
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(256, 4096) \
->Iterations(500)

REMOVEBENCH(ListRemove, List);
REMOVEBENCH(VectorRemove, Vector);
REMOVEBENCH(TreeRemove, Tree);
REMOVEBENCH(AvlTreeRemove, AvlTree);


#define RANGEBENCH(name, container) \
void name(benchmark::State& state) { \
  auto *c = new container<int>(); \
  for (auto _ : state) { \
    state.PauseTiming(); \
    delete c; \
    c = new container<int>(); \
    for (int i = 0; i < state.range(); ++i) \
    c->insert(rand(-10000, 10000)); \
    state.ResumeTiming(); \
    for(auto a : *c);\
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(256, 4096) \
->Iterations(500)

RANGEBENCH(ListRange, List);
RANGEBENCH(VectorRange, Vector);
RANGEBENCH(TreeRange, Tree);
RANGEBENCH(AvlTreeRange, AvlTree);

BENCHMARK_MAIN();

