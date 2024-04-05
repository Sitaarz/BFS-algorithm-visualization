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
private:
    int startNodeId;
    int endNodeId;
    const int rows;
    const int cols;
    int stepNumber = 0;

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

    void changeColor(int id, bool newColor) {
        emit colorChanged(id, newColor);
    }

    void startAnimation();

signals:
    void graphChanged();
    void rowsChanged();
    void colsChanged();
    void colorChanged(int id, bool newColor);

public slots:
    void startSearch();
};

#endif // BFS_CLASS_H
