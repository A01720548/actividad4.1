/**
 * @file Vertex.h
 * @author Esteban de la Maza, Ricardo Jasso, Raul Jerlach
 * @brief Vertex of graph
 * @version 0.1
 * @date 2020-11-15
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Vertex
{
private:
    /* data */
    string label;

public:
    Vertex(string name = "");
    vector<Vertex*> connections;
    string getName() { return this->label; }
    void addConnection(Vertex* who);
    void printNeighborhood();
    bool operator==(Vertex thatguy) { return thatguy.label == this->label; }

};

/**
 * @brief Construct a new Vertex:: Vertex object
 *
 * @param name
 */
Vertex::Vertex(string name)
{
    this->label = name;
}

/**
 * @brief Adds connections to nodes
 *
 * @param who Node to be connected
 */
void Vertex::addConnection(Vertex* who)
{
    this->connections.push_back(who);
}

/**
 * @brief Prints the Vertex's neighborhood
 *
 */
void Vertex::printNeighborhood()
{
    vector<Vertex*>::iterator it;
    for (it = this->connections.begin(); it != this->connections.end();it++) {
        cout << (*it)->getName() << " ";
    }
}