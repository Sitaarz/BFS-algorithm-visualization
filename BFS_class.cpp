#include "BFS_class.h"
#include <algorithm>
#include <tuple>
#include <QDebug>
#include <QMap>
#include <algorithm>
#include <Qthread>


BFS_class::BFS_class(int rows, int cols, int startNodeId, int endNodeId, QObject *parent)
    : QObject{parent}, rows(rows), cols(cols), startNodeId(startNodeId), endNodeId(endNodeId),
    currentAnimationFrame(0), timer(new QTimer(this)), milisecondsPerFrame(1000)
{
    connect(timer, &QTimer::timeout, this, &BFS_class::startAnimation);;
    inicializeGraph(rows, cols);
}

void BFS_class::inicializeGraph(int rows, int cols)
{
    graph.resize(rows);
    for(int i = 0; i < rows; i++){
        graph[i].resize(cols);
    }

    for(int i = 0 ; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::list<int> neighbours;

            std::tuple<int, int> currentIndex(i, j);

            std::tuple<int, int> leftNodeId(i, std::max(0, j-1));
            std::tuple<int, int> rightNodeId(i, std::min(j+1, cols-1));
            std::tuple<int, int> topNodeId(std::max(0, i-1), j);
            std::tuple<int, int> bottomNodeId(std::min(i+1, rows-1), j);

            if(leftNodeId != currentIndex) neighbours.push_back(i*rows+j-1);
            if(rightNodeId != currentIndex) neighbours.push_back(i*rows+j+1);
            if(topNodeId != currentIndex) neighbours.push_back( (i-1)*rows + j );
            if(bottomNodeId != currentIndex) neighbours.push_back( (i+1) * rows + j);

            graph[i][j] = Node(i*rows+j, neighbours);

            // qDebug() << graph[i][j].getId();
            // for(auto element: graph[i][j].neighbours){
            //     qDebug() << element;
            // }
            // qDebug() << "\n";
        }
    }
}



QVector<int> BFS_class::search()
{
    QMap<int, int> parent;
    QQueue<Node*> queue;
    QList<Node*> nodeList;
    QVector<int> path;


    QVector<QVector<Node>> buffor;
    buffor.resize(rows);
    for(int i = 0; i < cols; i++){
        buffor[i].resize(cols);
    }


    for(int i = 0; i < rows; i++){
        for(int j = 0; j< cols; j++){
            nodeList.append(&graph[i][j]);
        }
    }

    queue.enqueue(nodeList[startNodeId]);
    nodeList[startNodeId]->setVisited(true);

    for (int i =0; i< graph.size(); i++){
        for (int j = 0; j< graph[0].size(); j++){
            buffor[i][j] = graph[i][j];
        }
    }
    graphHistory.append(buffor);


    while (! queue.isEmpty()){
        Node* currentNode = queue.dequeue();
        stepNumber+=1;
        if(currentNode->getId() == endNodeId){
            qDebug() << "found";
            break;
        }
        // qDebug() << currentNode->getId();
        for(int neighbourId: currentNode->neighbours){
            Node* nieghbour = nodeList[neighbourId];
            if(!nieghbour->getVisited()){
                // changeColor(neighbourId, true);
                parent[neighbourId] = currentNode->getId();
                nieghbour->setVisited(true);
                queue.enqueue(nieghbour);

                for (int i =0; i< graph.size(); i++){
                    for (int j = 0; j< graph[0].size(); j++){
                        buffor[i][j] = graph[i][j];
                    }
                }
                graphHistory.append(buffor);

                // setGraph(getGraph());
                // emit graphChanged();
            }
        }

    }


    int currentId = endNodeId;
        while (currentId != startNodeId){
        path.append(currentId);
        currentId = parent[currentId];
    }
    path.append(currentId);
    std::reverse(path.begin(), path.end());

    // qDebug() << path;

    // QList<bool> newGraph;
    // for(Node* node: nodeList){
    //     newGraph.append(node->getVisited());
    // }

    timer->start(milisecondsPerFrame);
    return path;
}

QList<bool> BFS_class::getGraph() const
{
    QList<bool> resultList;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j< cols; j++){
            resultList.append(graph[i][j].getVisited());
        }
    }
    return resultList;
}

int BFS_class::getRows() const
{
    return rows;
}

int BFS_class::getCols() const
{
    return cols;
}

void BFS_class::startSearch()
{
    search();
}

void BFS_class::setGraph(const QList<bool> &newGraph)
{
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            graph[i][j].setVisited(newGraph[i*cols+j]);
        }
    }

    emit graphChanged();
}

void BFS_class::startAnimation()
{
    qDebug() << currentAnimationFrame;
    graph = graphHistory[currentAnimationFrame];

    // for (int i =0; i< graph.capacity(); i++){
    //     for (int j = 0; j< graph[0].size(); j++){
    //         qDebug() << graph[i][j].getVisited();
    //     }
    // }
    // qDebug() << '\n';

    currentAnimationFrame+=1;
    emit graphChanged();
    if(currentAnimationFrame == stepNumber) timer->stop();
}
