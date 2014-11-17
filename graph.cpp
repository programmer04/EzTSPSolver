#include "graph.h"
#include <QDebug>
#include <iostream>
#include <algorithm>
using namespace std;
Graph::Graph(int size,QObject *parent) :
    QObject(parent)
{
    potentialNewSize=size;
}

std::pair<int, std::vector<int> > Graph::bruteForce()
{
    printAdjacencyMatrix();
    long long min_cost=INF,cost;
    vector<int> hamiltonTour,bestHamiltonTour;
    vector<int> vertices;
    for(int vertex_num=0;vertex_num<size;vertex_num++)
        hamiltonTour.push_back(vertex_num);
    while(next_permutation(hamiltonTour.begin(),hamiltonTour.end())){
        cost=0;
        for(int index=0;index<size;index++){
            if(index==size-1)
                cost+=adj[hamiltonTour[size-1]][hamiltonTour[0]];
            else
                cost+=adj[hamiltonTour[index]][hamiltonTour[index+1]];
        }
        if(cost<min_cost)
            min_cost=cost,bestHamiltonTour=hamiltonTour;
    }
    bestHamiltonTour.push_back(bestHamiltonTour[0]);
    return make_pair(min_cost,bestHamiltonTour);
}

void Graph::printAdjacencyMatrix()
{
    QDebug graph=qDebug();
    for(int row=0;row<size;row++)
    {
        for(int column=0;column<size;column++)
            graph<<adj[row][column];
        graph<<endl;
    }
}

void Graph::edgeWeightChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
//    if(topLeft.row()>=size || topLeft.column()>=size) resize();
    adj[topLeft.row()][topLeft.column()]=topLeft.data().toInt();
}

void Graph::resize(int newSize)
{
    size=newSize;
    adj.resize(size);
    for(std::vector<std::vector<int> >::iterator it=adj.begin(); it!=adj.end();++it)
       it->resize(size);
}
