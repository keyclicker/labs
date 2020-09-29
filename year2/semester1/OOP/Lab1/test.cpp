#include <gtest/gtest.h>
#include "Algo.hpp"
#include "Graph.hpp"

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
  Graph gr;
  gr.resize(5);

  gr.addEdge(0, 4, 10);
  gr.addEdge(2, 4, 15);
  gr.addEdge(3, 0, 42);

  EXPECT_EQ(gr.getEdge(0, 4), 10);
  EXPECT_EQ(gr.getEdge(2, 4), 15);
  EXPECT_EQ(gr.getEdge(3, 0), 42);
}


TEST(Graph, ConnectEdges) {
  Graph gr;
  gr.resize(5);

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
  MatrixGraph gr;
  gr.resize(5);

  gr.addEdge(0, 4, 10);
  gr.addEdge(2, 4, 15);
  gr.addEdge(3, 0, 42);

  EXPECT_EQ(gr.getEdge(0, 4), 10);
  EXPECT_EQ(gr.getEdge(2, 4), 15);
  EXPECT_EQ(gr.getEdge(3, 0), 42);
}


TEST(MatrixGraph, ConnectEdges) {
  MatrixGraph gr;
  gr.resize(5);

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

