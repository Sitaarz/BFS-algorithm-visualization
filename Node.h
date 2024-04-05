#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <list>

class Node: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool visited READ getVisited WRITE setVisited NOTIFY visitedChanged)
private:
    bool visited;
    int id;

public:
    explicit Node(int id, std::list<int> neighbours, QObject *parent = nullptr);
    Node(const Node& other) : QObject(other.parent()), visited(other.visited), id(other.id) {}
    Node(){}

    std::list<int> neighbours;

    bool getVisited() const;

    void setVisited(bool isVisited);

    int getId();

    void setId(int id);

    Node& operator=(const Node& other);

signals:
    void visitedChanged();
};

#endif // NODE_H
