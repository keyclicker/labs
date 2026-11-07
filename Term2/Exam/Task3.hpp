#pragma once

#include <list>
#include <vector>
#include <algorithm>
using namespace std;

void addEdge(vector<list<size_t>> &graph, size_t v1, size_t v2) {
  if (find(graph[v1].begin(), graph[v1].end(), v2) == graph[v1].end())
    graph[v1].push_back(v2);

  if (find(graph[v2].begin(), graph[v2].end(), v1) == graph[v2].end())
    graph[v2].push_back(v1);
}