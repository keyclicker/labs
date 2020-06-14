## Requirements
- To build this lab you need **C++20**, **Boost** (boost::multi_array) and **Google Benchmark**
## Interactive mode
To run interactive mode choose **interactive** as executable in your IDLE
```
graph <name>                       Create set/matrix graph
add <name> <v1> <v2> <weight>      Add edge to graph
print <name>                       Print graph>
iscon <name>                       Is graph connected
istree <name>                      Is graph a tree
dfs <name>                         Print all vertices with DFS
bfs <name>                         Print all vertices with BFS
floyd <name>                       Print matrix of distance with Floyd Warshall
dijkstra <name>                    Print matrix of distance with Dijkstra Algo
topsrt <name>                      Print all vertices sorted with Topology Sort
span <name>                        Print spanning graph build with DFS
krus <name>                        Print min spanning graph build with Kruskal

'<command_name>' - for set graph
'<command_name>' + 'm' - for matrix graph
'add' for set graph and 'addm' for matrix graph
```

## Demo mode
- To run demo mode choose **demo** as executable in your IDLE

## Benchmark mode
- To run Benchmark mode choose **bench** as executable in your IDLE
- Pre-done benchmarks located in **Benchmarks** directory