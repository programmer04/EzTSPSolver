#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <vector>
#include <QModelIndex>
#include <utility>
class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(int size, QObject *parent);
    std::pair<int,std::vector<int> > bruteForce();
signals:

public slots:
    void edgeWeightChanged(const QModelIndex& topLeft,const QModelIndex& bottomRight);
    void resize(int newSize);
    void printAdjacencyMatrix();//for debugging purposes only
    void resize();
private:
    int size;
    int potentialNewSize;
    std::vector<std::vector<int> > adj;
    const int INF=1000000000;
};

#endif // GRAPH_H
