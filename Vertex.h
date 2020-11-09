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

Vertex::Vertex(string name)
{
    this->label = name;
}

void Vertex::addConnection(Vertex* who)
{
    this->connections.push_back(who);
}

void Vertex::printNeighborhood()
{
    vector<Vertex*>::iterator it;
    for (it = this->connections.begin(); it != this->connections.end();it++) {
        cout << (*it)->getName() << " ";
    }
}