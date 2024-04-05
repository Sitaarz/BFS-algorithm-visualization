#include "Node.h"


Node::Node(int id, std::list<int> neighbours, QObject *parent)
    :QObject{parent} ,neighbours(neighbours), id(id), visited(false)
{

}

bool Node::getVisited() const
{
    return visited;
}

void Node::setVisited(bool isVisited)
{
    visited = isVisited;
}

int Node::getId()
{
    return id;
}

void Node::setId(int id)
{
    this->id = id;
}

Node &Node::operator=(const Node &other)
{
    if(this != &other){
        id = other.id;
        visited = other.visited;
        neighbours = other.neighbours;
    }
    return *this;
}


