#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../UndirectedGraph.h"
#include "../../helper_functs.hpp"

using namespace std;

template<typename TV, typename TE>
struct Kruskal : public UnDirectedGraph<TV, TE> {
    UnDirectedGraph<TV, TE>* graph;
    Kruskal(UnDirectedGraph<TV, TE>* graph);

    UnDirectedGraph<TV, TE> apply();

};

template<typename TV, typename TE>
Kruskal<TV, TE>::Kruskal(UnDirectedGraph<TV, TE>* graph_)
{
    this->graph = graph_;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> Kruskal<TV, TE>::apply()
{
    UnDirectedGraph<TV, TE> mst;
    priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, weightComp<TV, TE>> pqueue;
    vector<Vertex<TV, TE>> visited;

    for (auto x: graph->vertexes)
    {
        mst.insertVertex(x.second);
        visited.push_back(x.second);
    }
}




#endif // KRUSKAL_H
