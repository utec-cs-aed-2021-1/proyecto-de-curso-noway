#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes[2];
    TE weight;
    Edge(Vertex<TV, TE>* v1, Vertex<TV, TE>* v2, TE weight){
        this->vertexes[0] = v1;
        this->vertexes[1] = v2;
        this->weight = weight;
    }
    void killSelf(){
        this->vertexes[0] = nullptr;
        this->vertexes[1] = nullptr;
        delete this;
    }
};

template<typename TV, typename TE>
struct Vertex {
    TV data;
    std::string id;
    std::list<Edge<TV, TE>*> edges;
    Vertex(TV data, const std::string& id){
        this->data = data;
        this->id = id;
    }
    void killSelf(){
        edges.clear();
        delete this;
    }
};

template<typename TV, typename TE>
class Graph{
protected:
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;

public:
    virtual bool insertVertex(string id, TV vertex) = 0;

    virtual bool createEdge(string id1, string id2, TE w) = 0;

    virtual bool deleteVertex(string id) = 0;

    virtual TE &operator()(string start, string end)= 0;

    virtual float density() = 0;

    virtual bool isDense(float threshold = 0.5) = 0;

    virtual bool isConnected()= 0;

    virtual bool isStronglyConnected() throw() = 0;

    virtual bool empty() = 0;

    virtual void clear()= 0;

    virtual void displayVertex(string id)= 0;

    virtual bool findById(string id) = 0;

    virtual void display() = 0;
};

#endif
