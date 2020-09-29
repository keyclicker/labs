#include <list>
#include <gtest/gtest.h>
#include "../src/Algo.hpp"
#include "../src/Graph.hpp"

TEST(Graph, CreationTest) {
  Graph gr;
  EXPECT_FALSE(gr.size());
}

TEST(Graph, SizeTest) {
  Graph gr;
  EXPECT_EQ(gr.size(), 0);

  gr.resize(5);
  EXPECT_EQ(gr.size(), 5);
}

TEST(Graph, AddEdge) {
  Graph gr(5);

  gr.addEdge(0, 4, 10);
  gr.addEdge(2, 4, 15);
  gr.addEdge(3, 0, 42);

  EXPECT_EQ(gr.getEdge(0, 4), 10);
  EXPECT_EQ(gr.getEdge(2, 4), 15);
  EXPECT_EQ(gr.getEdge(3, 0), 42);
}


TEST(Graph, ConnectEdges) {
  Graph gr(5);

  gr.connect(0, 4, 10);
  gr.connect(2, 4, 15);
  gr.connect(3, 0, 42);

  EXPECT_EQ(gr.getEdge(0, 4), 10);
  EXPECT_EQ(gr.getEdge(2, 4), 15);
  EXPECT_EQ(gr.getEdge(3, 0), 42);

  EXPECT_EQ(gr.getEdge(4, 0), 10);
  EXPECT_EQ(gr.getEdge(4, 2), 15);
  EXPECT_EQ(gr.getEdge(0, 3), 42);
}


TEST(MatrixGraph, CreationTest) {
  MatrixGraph gr;
  EXPECT_FALSE(gr.size());
}

TEST(MatrixGraph, SizeTest) {
  MatrixGraph gr;
  EXPECT_EQ(gr.size(), 0);

  gr.resize(5);
  EXPECT_EQ(gr.size(), 5);
}

TEST(MatrixGraph, AddEdge) {
  MatrixGraph gr(5);

  gr.addEdge(0, 4, 10);
  gr.addEdge(2, 4, 15);
  gr.addEdge(3, 0, 42);

  EXPECT_EQ(gr.getEdge(0, 4), 10);
  EXPECT_EQ(gr.getEdge(2, 4), 15);
  EXPECT_EQ(gr.getEdge(3, 0), 42);
}


TEST(MatrixGraph, ConnectEdges) {
  MatrixGraph gr(5);

  gr.connect(0, 4, 10);
  gr.connect(2, 4, 15);
  gr.connect(3, 0, 42);

  EXPECT_EQ(gr.getEdge(0, 4), 10);
  EXPECT_EQ(gr.getEdge(2, 4), 15);
  EXPECT_EQ(gr.getEdge(3, 0), 42);

  EXPECT_EQ(gr.getEdge(4, 0), 10);
  EXPECT_EQ(gr.getEdge(4, 2), 15);
  EXPECT_EQ(gr.getEdge(0, 3), 42);
}

TEST(GraphAlgorithms, IsConnected) {
  Graph uncon(4), con(3);
  uncon.connect(0, 1);
  uncon.connect(2, 3);

  con.connect(0,1);
  con.connect(1,2);

  EXPECT_FALSE(Algorithms::isConnected(uncon));
  EXPECT_TRUE(Algorithms::isConnected(con));
}

TEST(GraphAlgorithms, IsTree) {
  Graph tr(6), loop(3);

  tr.addEdge(0, 1);
  tr.addEdge(0, 2);
  tr.addEdge(1, 5);
  tr.addEdge(2, 3);
  tr.addEdge(2, 4);

  loop.addEdge(0, 1);
  loop.addEdge(1, 2);
  loop.addEdge(2, 0);

  EXPECT_TRUE(Algorithms::isTree(tr));
  EXPECT_FALSE(Algorithms::isTree(loop));
}

TEST(GraphAlgorithms, Dijkstra) {
  Graph gr1(5), gr2(4);

  gr1.addEdge(0, 1);
  gr1.addEdge(1, 4);
  gr1.addEdge(0, 2);
  gr1.addEdge(2, 3);
  gr1.addEdge(3, 4);

  gr2.addEdge(0, 3, 228);
  gr2.addEdge(0, 1, 40);
  gr2.addEdge(1, 2);
  gr2.addEdge(2, 3);

  EXPECT_EQ(Algorithms::dijkstra(gr1, 0, 4), 2);
  EXPECT_EQ(Algorithms::dijkstra(gr2, 0, 3), 42);
}

TEST(MatrixGraphAlgorithms, IsConnected) {
  MatrixGraph uncon(4), con(3);
  uncon.connect(0, 1);
  uncon.connect(2, 3);

  con.connect(0,1);
  con.connect(1,2);

  EXPECT_FALSE(Algorithms::isConnected(uncon));
  EXPECT_TRUE(Algorithms::isConnected(con));
}

TEST(MatrixGraphAlgorithms, IsTree) {
  MatrixGraph tr(6), loop(3);

  tr.addEdge(0, 1);
  tr.addEdge(0, 2);
  tr.addEdge(1, 5);
  tr.addEdge(2, 3);
  tr.addEdge(2, 4);

  loop.addEdge(0, 1);
  loop.addEdge(1, 2);
  loop.addEdge(2, 0);

  EXPECT_TRUE(Algorithms::isTree(tr));
  EXPECT_FALSE(Algorithms::isTree(loop));
}

TEST(MatrixGraphAlgorithms, Dijkstra) {
  MatrixGraph gr1(5), gr2(4);

  gr1.addEdge(0, 1);
  gr1.addEdge(1, 4);
  gr1.addEdge(0, 2);
  gr1.addEdge(2, 3);
  gr1.addEdge(3, 4);

  gr2.addEdge(0, 3, 228);
  gr2.addEdge(0, 1, 40);
  gr2.addEdge(1, 2);
  gr2.addEdge(2, 3);

  EXPECT_EQ(Algorithms::dijkstra(gr1, 0, 4), 2);
  EXPECT_EQ(Algorithms::dijkstra(gr2, 0, 3), 42);
}