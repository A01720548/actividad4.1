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
    graph.addEdge("C", "A");
    graph.addEdge("D", "C");
    graph.addEdge("D", "E");
    graph.addEdge("E", "F");

    graph.printGraph();

    graph.addEdge("E", "G");

    graph.printGraph();
}