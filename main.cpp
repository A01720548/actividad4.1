#include "Graph.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

main() {
    vector<string> V = { "A", "B", "C" };

    Graph graph = Graph(V);
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");
    graph.addEdge("C", "A");

    graph.printGraph();

}