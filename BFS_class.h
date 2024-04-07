#ifndef BFS_CLASS_H
#define BFS_CLASS_H

#include <QObject>
#include <Qvector>
#include <QQueue>
#include <QList>
#include "Node.h"
#include <QQmlListProperty>
#include <QTimer>

class BFS_class : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<bool> graph READ getGraph WRITE setGraph NOTIFY graphChanged)
    Q_PROPERTY(int rows READ getRows NOTIFY rowsChanged)
    Q_PROPERTY(int cols READ getCols NOTIFY colsChanged)
    Q_PROPERTY(int receivedInt READ getReceivedInt WRITE setReceivedInt NOTIFY receivedIntChanged)
    Q_PROPERTY(int startNodeId READ getStartNodeId WRITE setStartNodeId NOTIFY startNodeIdChanged)
    Q_PROPERTY(int endNodeId READ getEndNodeId WRITE setEndNodeId NOTIFY endNodeIdChanged)
private:
    int startNodeId;
    int endNodeId;
    int rows;
    int cols;
    int stepNumber;
    int m_receivedInt;
    QVector<int> shortestPath;

    QTimer *timer;
    int currentAnimationFrame;
    int milisecondsPerFrame;

    QVector<QVector<Node>> graph;
    QVector<QVector<QVector<Node>>> graphHistory;

    void inicializeGraph(int rows, int cols);


public:
    explicit BFS_class(int rows, int cols, int startNodeId, int endNodeId, QObject *parent = nullptr);

    QVector<int> search();
    QList<bool> getGraph() const;

    int getRows() const;

    int getCols() const;

    void setGraph(const QList<bool> &newGraph);

    void changeColor(int id, bool newColor);
    void reset();

    void startAnimation();

    int getReceivedInt() const;
    void setReceivedInt(int value);

    int getStartNodeId() const;
    void setStartNodeId(int newStartNode);

    int getEndNodeId() const;
    void setEndNodeId(int newEndNode);



signals:
    void graphChanged();
    void rowsChanged();
    void colsChanged();
    void colorChanged(int id, bool newColor);
    void receivedIntChanged();

    void startNodeIdChanged();
    void endNodeIdChanged();

public slots:
    void startSearch();
    void startReset();
    void showShortestPath();
};

inline void BFS_class::changeColor(int id, bool newColor) {
    emit colorChanged(id, newColor);
}

#endif // BFS_CLASS_H
