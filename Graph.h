#include <vector>
#include <string>
#include "Vertex.h"
#include <algorithm>
#include <iostream>

using namespace std;

class Graph
{
private:
    /* data */
    vector<Vertex> vertices;
    void DFS(Vertex* start, vector<Vertex*> visited);
    void BFS(Vertex* start, vector<Vertex*> visited);

public:
    Graph(vector<string> vertices);
    void addEdge(string u, string v);
    int getSize() { return this->vertices.size(); }
    void printGraph();
    void DFSWrapper(string x);
    void BFSWrapper(string x);

};

/**
 * @brief Construct a new Graph:: Graph object
 *
 * @param vertices
 */
Graph::Graph(vector<string> vertices) {
    vector<string>::iterator it;

    for (it = vertices.begin(); it != vertices.end(); it++) {
        Vertex newboy = Vertex(*it);
        this->vertices.push_back(newboy);
    }
}

/**
 * @brief Adds and edge between two vertices
 *
 * @param u A string representing the label of a vertex
 * @param v A string representing the label of a vertex
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

void Graph::DFSWrapper(string x)
{
    vector<Vertex>::iterator px;
    px = find(this->vertices.begin(), this->vertices.end(), x);
    Vertex* X = &this->vertices[px - this->vertices.begin()];
    vector<Vertex*> visited;
    DFS(X, visited);

}

void Graph::BFSWrapper(string x)
{
    vector<Vertex>::iterator px;
    px = find(this->vertices.begin(), this->vertices.end(), x);
    Vertex* X = &this->vertices[px - this->vertices.begin()];
    vector<Vertex*> visited;
    BFS(X, visited);
}



void Graph::DFS(Vertex* start, vector<Vertex*> visited)
{
    visited.push_back(start);

    cout << start->getName() << " ";
    vector<Vertex*>::iterator it;
    for (it = start->connections.begin(); it != start->connections.end();++it) {
        vector<Vertex*>::iterator it2;
        it2 = std::find(visited.begin(), visited.end(), (*it));
        if (it2 == visited.end()) {
            visited.push_back((*it));
            DFS((*it), visited);

        }

    }

}

void Graph::BFS(Vertex* start, vector<Vertex*> visited)
{
    visited.push_back(start);
    vector<Vertex*> queue;
    queue.push_back(start);
    vector<Vertex*>::iterator it;

    while (!queue.empty()) {
        start = queue.front();
        cout << start->getName() << " ";
        queue.erase(queue.begin());

        for (it = start->connections.begin(); it != start->connections.end();++it) {
            vector<Vertex*>::iterator it2;
            it2 = std::find(visited.begin(), visited.end(), (*it));
            if (it2 == visited.end()) {
                visited.push_back((*it));
                queue.push_back((*it));
            }
        }

    }

}