#include "Matrix.hpp"
#include <benchmark/benchmark.h>
using namespace std;

void testDefault(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    std::size_t size = state.range();
    Matrix<int> c(size, size), d(size, size);

    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        c.set(i, j, rand() % 20 - 10);
        d.set(i, j, rand() % 20 - 10);
      }
    }

    state.ResumeTiming();

    c*d;
  };
}
BENCHMARK(testDefault)
->Unit(benchmark::TimeUnit::kMillisecond)
->RangeMultiplier(2)
->Range(64, 1024);


void testStrassen64(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    std::size_t size = state.range();
    Matrix<int> c(size, size), d(size, size);

    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        c.set(i, j, rand() % 20 - 10);
        d.set(i, j, rand() % 20 - 10);
      }
    }

    state.ResumeTiming();
    c.strassenMultiply(d);
  };
}
BENCHMARK(testStrassen64)
        ->Unit(benchmark::TimeUnit::kMillisecond)
        ->RangeMultiplier(2)
        ->Range(64, 1024);

//void testRawStrassen(benchmark::State& state) {
//  for (auto _ : state) {
//    state.PauseTiming();
//
//    std::size_t size = state.range();
//    Matrix<int> c(size, size), d(size, size);
//
//    srand(time(NULL));
//    for (int i = 0; i < size; ++i) {
//      for (int j = 0; j < size; ++j) {
//        c.set(i, j, rand() % 20 - 10);
//        d.set(i, j, rand() % 20 - 10);
//      }
//    }
//
//    state.ResumeTiming();
//    c.strassenMultiply(d, 2);
//  };
//}
//BENCHMARK(testRawStrassen)
//        ->Unit(benchmark::TimeUnit::kMillisecond)
//        ->RangeMultiplier(2)
//        ->Range(2, 256);


//void testStrassenThreshold(benchmark::State& state) {
//  for (auto _ : state) {
//    state.PauseTiming();
//    std::size_t size = 512;
//    Matrix<int> c(size, size), d(size, size);
//
//    srand(time(NULL));
//    for (int i = 0; i < size; ++i) {
//      for (int j = 0; j < size; ++j) {
//        c.set(i, j, rand() % 20 - 10);
//        d.set(i, j, rand() % 20 - 10);
//      }
//    }
//    state.ResumeTiming();
//    c.strassenMultiply(d, state.range());
//  };
//}
//BENCHMARK(testStrassenThreshold)
//->Unit(benchmark::TimeUnit::kMillisecond)
//->RangeMultiplier(2)
//->Range(2, 512);




BENCHMARK_MAIN();