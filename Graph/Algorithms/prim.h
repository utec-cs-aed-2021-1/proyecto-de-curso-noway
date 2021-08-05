#ifndef PRIM_H
#define PRIM_H

#include "../UndirectedGraph.h"
using namespace std;

template<typename TV, typename TE>
using edgeVertex = pair<Edge<TV, TE>*, Vertex<TV, TE>*>;    //for convenience

template<typename TV, typename TE>
struct weightComp {
    bool operator() (edgeVertex<TV, TE> ev1, edgeVertex<TV, TE> ev2)            // struct to be used in priority_queue
    {
        return ev1.first->weight > ev2.first->weight;           // built the same way as std::greater
    }
};

template<typename TV, typename TE>
struct Prim : public UnDirectedGraph<TV, TE>{
    string startID;
    UnDirectedGraph<TV, TE>* graph;

    Prim(UnDirectedGraph<TV, TE>* graph_, const string startID_);

    UnDirectedGraph<TV, TE> apply();

};

template<typename TV, typename TE>
Prim<TV, TE>::Prim(UnDirectedGraph<TV, TE>* graph_, const string startID_)
{
    if (graph_->findById(startID_) == false) throw "The selected vertex is not in the graph";

    this->startID = startID_;
    this->graph = graph_;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> Prim<TV, TE>::apply()
{
    UnDirectedGraph<TV, TE> mst;
    priority_queue<edgeVertex<TV, TE>, vector<edgeVertex<TV, TE>>, weightComp<TV, TE>> pqueue;
    vector<Vertex<TV, TE>> visited;

    mst.insertVertex(graph.getVertex(startID));
    for (auto x: graph.getVertex(startID)->edges)
        pqueue.push(make_pair(x, graph.getVertex(startID)));




}





#endif // PRIM_H
