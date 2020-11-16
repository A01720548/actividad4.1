/**
 * @file Graph.h
 * @author Esteban de la Maza, Ricardo Jasso, Raul Jerlach
 * @brief Graph class with DFS, BFS, isTree and isBipartite
 * @version 0.1
 * @date 2020-11-15
 *
 * @copyright Copyright (c) 2020
 *
 */
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
    bool isCycle(Vertex* node, vector<Vertex*>& visited, Vertex* parent);
    bool isBipartite(Vertex* node, vector<Vertex*>& visited, vector<Vertex*>& red, vector<Vertex*>& blue);



public:
    Graph(vector<string> vertices);
    void addEdge(string u, string v);
    int getSize() { return this->vertices.size(); }
    void printGraph();
    void DFSWrapper(string x);
    void BFSWrapper(string x);

    bool isTree(string x);
    bool isBipartiteWrapper(string x);
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

/**
 * @brief Prints the graph
 *
 * Complexity: O(n)
 */
void Graph::printGraph() {
    vector<Vertex>::iterator it;

    for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
        auto current = this->vertices[it - this->vertices.begin()];
        cout << current.getName() << " has the following connections [";
        current.printNeighborhood();
        cout << "]" << endl;
    }
}

/**
 * @brief Wrapper function that calls the main DFS function
 *        and creates the vector to keep track of visited nodes
 *
 * @param x string for starting point for the DFS
 */
void Graph::DFSWrapper(string x)
{
    vector<Vertex>::iterator px;
    px = find(this->vertices.begin(), this->vertices.end(), x);
    Vertex* X = &this->vertices[px - this->vertices.begin()];
    vector<Vertex*> visited;
    DFS(X, visited);

}

/**
 * @brief Wrapper function that calls the main BFS function
 *        and creates the vector to keep track of visited nodes
 *
 * @param x string for starting point for the BFS
 */
void Graph::BFSWrapper(string x)
{
    vector<Vertex>::iterator px;
    px = find(this->vertices.begin(), this->vertices.end(), x);
    Vertex* X = &this->vertices[px - this->vertices.begin()];
    vector<Vertex*> visited;
    BFS(X, visited);
}
/**
 * @brief Wrapper function to call cyclic function
 * Complexity: O(1)
 * @param x String of start node
 * @return true If graph is tree
 * @return false If graph isnt tree
 */
bool Graph::isTree(string x)
{
    vector<Vertex>::iterator px;
    px = find(this->vertices.begin(), this->vertices.end(), x);
    Vertex* X = &this->vertices[px - this->vertices.begin()];
    vector<Vertex*> visited;
    Vertex* parent = new Vertex();

    if (isCycle(X, visited, parent)) {
        return false;
    }

    if (visited.size() < getSize()) {
        return false;
    }

    return true;
}
/**
 * @brief Wrapper function to call recursive Bipartite Function
 * Complexity: O(1)
 * @param x String of start node
 * @return true If graph is bipartite
 * @return false If graph isnt bipartite
 */
bool Graph::isBipartiteWrapper(string x)
{
    vector<Vertex>::iterator px;
    px = find(this->vertices.begin(), this->vertices.end(), x);
    Vertex* X = &this->vertices[px - this->vertices.begin()];
    vector<Vertex*> visited, red, blue;
    red.push_back(X);
    if (isBipartite(X, visited, red, blue)) {
        return true;
    }
    else {
        return false;
    }

}
/**
 * @brief Recursive function to tell if graph is bipartite
 * Complexity: O(n)
 * @param node Current node
 * @param visited Vector of past nodes that have been visited
 * @param red Vector of nodes with red color
 * @param blue Vector of nodes with blue color
 * @return true If graph is bipartite
 * @return false If graph isnt bipartite
 */
bool Graph::isBipartite(Vertex* node, vector<Vertex*>& visited, vector<Vertex*>& red, vector<Vertex*>& blue)
{
    visited.push_back(node);
    vector<Vertex*>::iterator it, itRojo, itAzul;
    itRojo = std::find(red.begin(), red.end(), node);
    itAzul = std::find(blue.begin(), blue.end(), node);
    for (it = node->connections.begin(); it != node->connections.end();++it) {
        vector<Vertex*>::iterator it2;
        it2 = std::find(visited.begin(), visited.end(), (*it));
        if (it2 == visited.end()) {
            if (itRojo != red.end()) {
                blue.push_back((*it));
                if (!isBipartite((*it), visited, red, blue)) {
                    return false;
                }
            }
            else if (itAzul != blue.end()) {
                red.push_back((*it));
                if (!isBipartite((*it), visited, red, blue)) {
                    return false;
                }
            }
        }
        else if (itRojo != red.end() && itAzul != blue.end()) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Recursive function to tell if a graph is a cycle
* Complexity: O(n)
 * @param node Current node
 * @param visited Vector of past nodes that have been visited
 * @param parent Parent of current node
 * @return true If graph is a cycle
 * @return false If graph isnt a cycle
 */
bool Graph::isCycle(Vertex* node, vector<Vertex*>& visited, Vertex* parent)
{
    visited.push_back(node);

    vector<Vertex*>::iterator it;
    for (it = node->connections.begin(); it != node->connections.end();++it) {
        vector<Vertex*>::iterator it2;
        it2 = std::find(visited.begin(), visited.end(), (*it));
        if (it2 == visited.end()) {
            if (isCycle(*it, visited, node)) {
                return true;
            }
        }
        else if (*it != parent) {
            return true;
        }
    }
    return false;
}


/**
 * @brief Function for Depth First Search
 *
 * @param start value that indicates the starting node in the graph
 * @param visited vector of vertex type pointers to keep track of visited nodes
 *
 *  * Complexity: O(n)
 */
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

/**
 * @brief Funcion for Breadth First Search
 *
 * @param start value that indicates the starting node in the graph
 * @param visited vector of vertex type pointers to keep track of visited nodes
 *
 * Complexity: O(n)
 */
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