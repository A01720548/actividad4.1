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
        Vertex* U = new Vertex(u);
        Vertex* V = new Vertex(v);
        U->addConnection(V);
        V->addConnection(U);
        this->vertices.push_back(*U);
        this->vertices.push_back(*V);
    }
    else if (pv == this->vertices.end()) {
        // only pu exists, add V and find U
        Vertex* U = &this->vertices[pu - this->vertices.begin()];
        Vertex* V = new Vertex(v);
        U->addConnection(V);
        V->addConnection(U);
        this->vertices.push_back(*V);
    }
    else if (pu == this->vertices.end()) {
        // only pv exists, add U and find V
        Vertex* U = new Vertex(u);
        Vertex* V = &this->vertices[pv - this->vertices.begin()];
        U->addConnection(V);
        V->addConnection(U);
        this->vertices.push_back(*U);
    }
    else {
        // both exist, find them
        Vertex* U = &this->vertices[pu - this->vertices.begin()];
        Vertex* V = &this->vertices[pv - this->vertices.begin()];
        U->addConnection(V);
        V->addConnection(U);
    }

}

void Graph::printGraph() {
    vector<Vertex>::iterator it;
    for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
        auto current = this->vertices[it - this->vertices.begin()];
        cout << current.getName() << " has the following connections [";
        current.printNeighborhood();
        cout << "]" << endl;
    }
}



