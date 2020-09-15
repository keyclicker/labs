#include "List.hpp"
#include "Vector.hpp"
#include "Array.hpp"
#include <list>
#include <vector>
#include <array>

#include <iostream>

#include <benchmark/benchmark.h>
using namespace std;


#define PUSHBENCH(name, container, func) \
void name(benchmark::State& state) { \
  auto *c = new container<int>(); \
  for (auto _ : state) { \
    state.PauseTiming(); \
    delete c; \
    c = new container<int>(state.range()); \
    state.ResumeTiming(); \
    for (int i = 0; i < state.range(); ++i) \
      c->func; \
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(512, 4096) \

PUSHBENCH(ListPushBack, List, push_back(0));
PUSHBENCH(STDListPushBack, list, push_back(0));
PUSHBENCH(STDListEmplaceBack, list, emplace_back(0));
PUSHBENCH(VectorPushBack, Vector, push_back(0));
PUSHBENCH(STDVectorPushBack, vector, push_back(0));
PUSHBENCH(STDVectorEmplaceBack, vector, emplace_back(0));

PUSHBENCH(ListPushFront, List, push_front(0));
PUSHBENCH(STDListPushFront, list, push_front(0));
PUSHBENCH(STDListEmplaceFront, list, emplace_front(0));
PUSHBENCH(VectorPushFront, Vector, push_front(0));
PUSHBENCH(STDVectorIsertBegin, vector, insert(c->begin(), 0));
PUSHBENCH(STDVectorEmplaceBegin, vector, emplace(c->begin(), 0));

PUSHBENCH(ListInsertBegin, List, insert(0, 0));
PUSHBENCH(STDListInsertBegin, list, insert(c->begin(), 0));
PUSHBENCH(VectorInsertBegin, Vector, insert(0, 0));
PUSHBENCH(STDVectorInsertBegin, vector, insert(c->begin(), 0));

#define RANGEBENCH(name, container) \
void name(benchmark::State& state) { \
  auto *c = new container<int>(); \
  for (auto _ : state) { \
    state.PauseTiming(); \
    delete c; \
    c = new container<int>(state.range()); \
    state.ResumeTiming(); \
    for(auto a : *c);\
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(512, 4096) \
->Iterations(8000)

RANGEBENCH(ListForRange, List);
RANGEBENCH(STDListForRange, list);
RANGEBENCH(VectorForRange, Vector);
RANGEBENCH(STDVectorForRange, vector);

#define INITBENCH(name, container) \
void name(benchmark::State& state) { \
  container<int> *c; \
  for (auto _ : state) { \
    c = new container<int>(state.range()); \
    state.PauseTiming(); \
    delete c; \
    state.ResumeTiming(); \
  }; \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(512, 4096)

INITBENCH(ListInitWithZero, List);
INITBENCH(STDListInitWithZero, list);
INITBENCH(VectorInitWithZero, Vector);
INITBENCH(STDVectorInitWithZero, vector);


#define ERASEBENCH(name, container, func) \
void name(benchmark::State& state) { \
  auto *c = new container<int>(); \
  for (auto _ : state) { \
    state.PauseTiming(); \
    delete c; \
    c = new container<int>(state.range()); \
    state.ResumeTiming(); \
    c->func; \
  } \
} \
BENCHMARK(name) \
->Unit(benchmark::TimeUnit::kMicrosecond) \
->RangeMultiplier(2) \
->Range(512, 4096) \
->Iterations(8000)

ERASEBENCH(ListEraseBegin, List, erase(0));
ERASEBENCH(STDListEraseBegin, list, erase(c->begin()));
ERASEBENCH(VectorEraseBegin, Vector, erase(0));
ERASEBENCH(STDVectorEraseBegin, vector, erase(c->begin()));


BENCHMARK_MAIN();


