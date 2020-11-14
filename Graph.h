#include "Vertex.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Graph
{
private:
    /* data */
    vector<Vertex> vertices;


public:
    Graph(vector<string> vertices);
    void addEdge(string u, string v);
    int getSize() { return this->vertices.size(); }
    void printGraph();
    bool DFS(Vertex* start);

};
/**
 * @brief Construct a new Graph:: Graph object
 *
 * @param vertices
 */
Graph::Graph(vector<string> vertices)
{
    vector<string>::iterator it;

    for (it = vertices.begin(); it != vertices.end(); it++) {
        Vertex newboy = Vertex(*it);
        this->vertices.push_back(newboy);
    }
}
/**
 * @brief Adds an edge between 2 vertices
 *
 * @param u string representing label of a vertex
 * @param v string representing label of another vertex
 */
void Graph::addEdge(string u, string v) {

    // addEdge(A, B)

    vector<Vertex>::iterator pu, pv;
    pu = find(this->vertices.begin(), this->vertices.end(), u);
    pv = find(this->vertices.begin(), this->vertices.end(), v);

    if (pu == this->vertices.end() && pv == this->vertices.end()) {
        //if they dont exist, add them
        auto U = make_shared<Vertex>(u);
        auto V = make_shared<Vertex>(v);
        U->addConnection(*V);
        V->addConnection(*U);
        this->vertices.push_back(*U);
        this->vertices.push_back(*V);
    }
    else if (pv == this->vertices.end()) {
        // only pu exists, add V and find U
        Vertex* U = &(*pu);
        auto V = make_shared<Vertex>(v);
        U->addConnection(*V);
        V->addConnection(*U);
        this->vertices.push_back(*V);
    }
    else if (pu == this->vertices.end()) {
        // only pv exists, add U and find V
        Vertex* V = &(*pv);
        auto U = make_shared<Vertex>(u);
        U->addConnection(*V);
        V->addConnection(*U);
        this->vertices.push_back(*V);
    }
    else {
        // both exist, find them
        Vertex* V = &(*pv);
        Vertex* U = &(*pu);
        U->addConnection(*V);
        V->addConnection(*U);
    }

}

void Graph::printGraph() {
    vector<Vertex>::iterator it;
    for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
        Vertex current = *it;
        cout << current.getName() << " has the following connections [";
        current.printNeighborhood();
        cout << "]" << endl;
    }
}

bool Graph::DFS(Vertex* start)
{
    start->visited = true;
    vector<shared_ptr<Vertex>>::iterator it;
    for (it = start->connections.begin(); it != start->connections.end(); it++) {
        DFS(&*it);
    }
    // start.connections
}




