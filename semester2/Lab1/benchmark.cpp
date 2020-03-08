#include <benchmark/benchmark.h>
#include "Database.hpp"
#include "Message.hpp"

Database<Message> testdb = Database<Message>::Generate(1000);


void SaveToTextFile(benchmark::State& state) {
  while (state.KeepRunning()) testdb.saveToTextFile("bench.txt");
}
BENCHMARK(SaveToTextFile)->Unit(benchmark::TimeUnit::kMillisecond);

void SaveToBinFile(benchmark::State& state) {
  while (state.KeepRunning()) testdb.saveToBinFile("bench.bin");
}
BENCHMARK(SaveToBinFile)->Unit(benchmark::TimeUnit::kMillisecond);

void LoadFromTextFile(benchmark::State& state) {
  while (state.KeepRunning()) testdb.loadFromTextFile("bench.txt");
}
BENCHMARK(LoadFromTextFile)->Unit(benchmark::TimeUnit::kMillisecond);

void LoadFromBinFile(benchmark::State& state) {
  while (state.KeepRunning()) testdb.loadFromBinFile("bench.bin");
}
BENCHMARK(LoadFromBinFile)->Unit(benchmark::TimeUnit::kMillisecond);

void AddFromTextFile(benchmark::State& state) {
  while (state.KeepRunning()) testdb.addFromTextFile("bench.txt");
}
BENCHMARK(AddFromTextFile)->Unit(benchmark::TimeUnit::kMillisecond);

void AddFromBinFile(benchmark::State& state) {
  while (state.KeepRunning()) testdb.addFromBinFile("bench.bin");
}
BENCHMARK(AddFromBinFile)->Unit(benchmark::TimeUnit::kMillisecond);

BENCHMARK_MAIN();