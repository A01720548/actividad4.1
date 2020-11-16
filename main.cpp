#include "Graph.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

main() {
    vector<string> V = { "A", "B", "C", "D", "E" };
    vector<string> V2 = { "A", "B", "C" };

    Graph graph = Graph(V);
    Graph graph2 = Graph(V2);
    Graph graph3 = Graph(V);

    //Is Bipartite + Not Tree
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");
    graph.addEdge("C", "D");
    graph.addEdge("D", "E");
    graph.addEdge("E", "F");
    graph.addEdge("F", "A");

    //Not Bipartite + Not Tree
    graph2.addEdge("A", "B");
    graph2.addEdge("B", "C");
    graph2.addEdge("C", "A");

    //Is Bipartite + Is Tree
    graph3.addEdge("B", "A");
    graph3.addEdge("A", "C");
    graph3.addEdge("A", "D");
    graph3.addEdge("D", "E");

    graph.isTree("A") ? cout << "Graph is Tree\n" : cout << "Graph is not Tree\n";
    graph2.isTree("A") ? cout << "Graph 2 is Tree\n" : cout << "Graph 2 is not Tree\n";
    graph3.isTree("A") ? cout << "Graph 3 is Tree\n" : cout << "Graph 3 is not Tree\n";

    cout << endl;

    graph.isBipartiteWrapper("A") ? cout << "Graph is Bipartite\n" : cout << "Graph is not Bipartite\n";
    graph2.isBipartiteWrapper("A") ? cout << "Graph 2 is Bipartite\n" : cout << "Graph 2 is not Bipartite\n";
    graph3.isBipartiteWrapper("A") ? cout << "Graph 3 is Bipartite\n" : cout << "Graph 3 is not Bipartite\n";

    cout << endl;

    //DFS
    cout << "Graph 1: ";
    graph.DFSWrapper("A");
    cout << endl << "Graph 2: ";
    graph2.DFSWrapper("A");
    cout << endl << "Graph 3: ";
    graph3.DFSWrapper("A");

    cout << endl;
    cout << endl;

    //BFS
    cout << "Graph 1: ";
    graph.BFSWrapper("A");
    cout << endl << "Graph 2: ";
    graph2.BFSWrapper("A");
    cout << endl << "Graph 3: ";
    graph3.BFSWrapper("A");


    //graph.printGraph();
}