#include <gtest/gtest.h>

#include "Graph.hpp"
#include "Multisort.hpp"
#include <random>


#define G_SIZE 200

TEST(Graph, FloydComp) {
  Graph<double> graph(G_SIZE);

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int>
      rec(0, G_SIZE * G_SIZE), randEdge(0, G_SIZE - 1), isDir(0, 1);
  std::uniform_real_distribution<double> weight(0.1, 10.0);

  for (int i = 0; i < rec(mt); ++i) {
    if (isDir(mt))
      graph.addDirEdge(randEdge(mt), randEdge(mt), weight(mt));
    else
      graph.addUndirEdge(randEdge(mt), randEdge(mt), weight(mt));
  }

  auto onet = graph.floydWarshall();
  auto multit = graph.floydWarshallMulti();

  int dif = 0;
  for (int i = 0; i < onet.size(); ++i) {
    for (int j = 0; j < onet.size(); ++j) {
      if (onet[i][j] != multit[i][j]) ++dif;
    }
  }

  std::cout << onet << '\n' << multit << std::endl;

  std::cout << dif << std::endl;

  EXPECT_EQ(onet, multit);
}


int rand(int a, int b) {
  static std::random_device rd;
  static std::default_random_engine re(rd());
  std::uniform_int_distribution<int> drand(a, b);
  return drand(re);
}


TEST(Sort, Quick) {
  std::vector<int> a;
  for (int i = 0; i < 1000; ++i)
    a.push_back(rand(0, 2024));
  std::vector<int> b = a;

  std::sort(a.begin(), a.end());
  quicksort(b.begin(), b.end());

  EXPECT_EQ(a, b);
}

TEST(Sort, QuickAsync) {
  std::vector<int> a;
  for (int i = 0; i < 1000; ++i)
    a.push_back(rand(0, 2024));
  std::vector<int> b = a;

  std::sort(a.begin(), a.end());
  quicksort_async(b.begin(), b.end());

  EXPECT_EQ(a, b);
}

TEST(Sort, Merge) {
  std::vector<int> a;
  for (int i = 0; i < 1000; ++i)
    a.push_back(rand(0, 2024));
  std::vector<int> b = a;

  std::sort(a.begin(), a.end());
  merge(b.begin(), b.end());

  EXPECT_EQ(a, b);
}


TEST(Sort, MergeAsync) {
  std::vector<int> a;
  for (int i = 0; i < 1000; ++i)
    a.push_back(rand(0, 2024));
  std::vector<int> b = a;

  std::sort(a.begin(), a.end());
  merge_async(b.begin(), b.end());

  EXPECT_EQ(a, b);
}