#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

class Vertex
{
private:
    /* data */
    string label;

public:
    Vertex(string name = "");
    vector<shared_ptr<Vertex>> connections;

    string getName() { return this->label; }
    void addConnection(Vertex who);
    void printNeighborhood();
    bool operator==(Vertex thatguy) { return thatguy.label == this->label; }

};

Vertex::Vertex(string name)
{
    this->label = name;
}

void Vertex::addConnection(Vertex who)
{
    shared_ptr<Vertex> neighbor = make_shared<Vertex>(who);
    this->connections.push_back(neighbor);
}

void Vertex::printNeighborhood()
{
    vector<shared_ptr<Vertex>>::iterator it;
    for (it = this->connections.begin(); it != this->connections.end();it++) {
        cout << (*it)->getName() << " ";
    }
}