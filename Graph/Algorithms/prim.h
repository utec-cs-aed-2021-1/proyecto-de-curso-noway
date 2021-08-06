#ifndef PRIM_H
#define PRIM_H

#include "../UndirectedGraph.h"
#include "../../helper_functs.hpp"

using namespace std;

//template<typename TV, typename TE>                            //located in helper_functs
//using edgeVertex = pair<Edge<TV, TE>*, Vertex<TV, TE>*>;    //for convenience


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

    visited.push_back(graph.getVertex(startID));

    while (!pqueue.empty())
    {
        auto* it = find(visited.begin(), visited.end(), pqueue.top().second);
        while (it != visited.end()) {
            it = find(visited.begin(), visited.end(), pqueue.top().second);
            pqueue.pop();
        }
        mst.createEdge(pqueue.top().first->vertexes[0], pqueue.top().second, pqueue.top().first->weight);
        for (auto x: mst)
    }


}





#endif // PRIM_H
