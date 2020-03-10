#include "Database.hpp"
#include "Message.hpp"
#include <benchmark/benchmark.h>
#include <fstream>
#include <filesystem>
using namespace std;


#define MYBENCH(x) BENCHMARK(x) \
->Unit(benchmark::TimeUnit::kMillisecond) \
->RangeMultiplier(4) \
->Range(512, 512<<4);

void SaveToTextFile(benchmark::State& state) {
  Database<Message> testdb = Database<Message>::Generate(state.range());
  for (auto _ : state) testdb.saveToTextFile("bench.txt");
}
MYBENCH(SaveToTextFile);

void SaveToBinFile(benchmark::State& state) {
  Database<Message> testdb = Database<Message>::Generate(state.range());
  for (auto _ : state) testdb.saveToBinFile("bench.bin");
}
MYBENCH(SaveToBinFile);

void LoadFromTextFile(benchmark::State& state) {
  Database<Message> testdb = Database<Message>::Generate(state.range());
  testdb.saveToTextFile("bench.txt");

  for (auto _ : state) testdb.loadFromTextFile("bench.txt");
}
MYBENCH(LoadFromTextFile);

void LoadFromBinFile(benchmark::State& state) {
  Database<Message> testdb = Database<Message>::Generate(state.range());
  testdb.saveToBinFile("bench.bin");

  for (auto _ : state) testdb.loadFromBinFile("bench.bin");
}
MYBENCH(LoadFromBinFile);


int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();

  ofstream out("benchmark.log", ios::app);

  out << "\n-------------------------------" << endl;
  out << "File                      Size" << endl;
  out << "-------------------------------" << endl;

  for (int i = 512; i < 512 * 32; i*=2) {
    Database<Message> testdb = Database<Message>::Generate(i);

    testdb.saveToTextFile("bench.txt");
    testdb.saveToBinFile("bench.bin");

    out << setw(25) << left << "bench.txt/" + to_string(i) << filesystem::file_size("bench.txt") << endl;
    out << setw(25) << left << "bench.bin/" + to_string(i) << filesystem::file_size("bench.bin") << endl;
  }
}