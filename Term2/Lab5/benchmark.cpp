#include "Graph.hpp"
#include "Algo.hpp"

#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

#include <benchmark/benchmark.h>

template<typename T>
auto rand(T a, T b) {
  random_device rd;
  default_random_engine re(rd());
  uniform_int_distribution<T> drand(a, b);
  return drand(re);
}


#define GRAPHBENCH(name, gr, algo) \
void name(benchmark::State& state) {\
  for (auto _ : state) {\
    state.PauseTiming();\
      gr<int> g(state.range());\
      auto ecnt = (state.range() * state.range()) / 2;\
      for (int i = 0; i < ecnt; ++i)\
        g.addEdge(rand(long(0), state.range()-1), \
                rand(long(0), state.range()-1), rand(1, 8));\
    state.ResumeTiming();\
    algo(g);\
  };\
}\
BENCHMARK(name)\
->Unit(benchmark::TimeUnit::kMillisecond)\
->RangeMultiplier(2)\
->Range(128, 1024) \
->Iterations(1)

GRAPHBENCH(SetIsTree, Graph, Algorithms::isTree);
GRAPHBENCH(MatrixIsTree, MatrixGraph, Algorithms::isTree);
GRAPHBENCH(SetIsConnected, Graph, Algorithms::isConnected);
GRAPHBENCH(MatrixIsConnected, MatrixGraph, Algorithms::isConnected);

GRAPHBENCH(SetKruskal, Graph, Algorithms::kruskal);
GRAPHBENCH(MatrixKruskal, MatrixGraph, Algorithms::kruskal);
GRAPHBENCH(SetSpanningTree, Graph, Algorithms::spanningTree);
GRAPHBENCH(MatrixSpanningTree, MatrixGraph, Algorithms::spanningTree);

GRAPHBENCH(SetDijkstra, Graph, Algorithms::dijkstra);
GRAPHBENCH(MatrixDijkstra, MatrixGraph, Algorithms::dijkstra);
GRAPHBENCH(SetFloydWarshall, Graph, Algorithms::floydWarshall);
GRAPHBENCH(MatrixFloydWarshall, MatrixGraph, Algorithms::floydWarshall);


BENCHMARK_MAIN();

