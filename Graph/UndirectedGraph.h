#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
using namespace std;

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
public:
    UnDirectedGraph();
    ~UnDirectedGraph();
    bool insertVertex(string id, TV vertex) override;
    bool createEdge(string id1, string id2, TE w) override;
    bool deleteVertex(string id) override;
    bool deleteEdge(string id) override;
    TE &operator()(string start, string end) override;
    float density() override;
    bool isDense(float threshold = 0.5) override;
    bool isConnected() override;
    bool isStronglyConnected() throw();
    bool empty();
    void clear() override;

    void displayVertex(string id) override;
    bool findById(string id) override;
    void display() override;
};

template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::UnDirectedGraph() = default;

template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::~UnDirectedGraph() {
    if (!this->vertexes.empty())
        clear();
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {
    if (!findById(id)) {
        auto* v = new Vertex<TV, TE>(vertex, id);
        this->vertexes[id] = v;
        return true;
    }

    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
    if(!findById(id1) || !findById(id2)){
        throw invalid_argument("IDs not found.");
        return false;
    }
    if(id1 == id2){
        throw invalid_argument("IDs are same");
        return false;
    }
    Vertex<TV, TE>* vertex1 = this->vertexes[id1];
    Vertex<TV, TE>* vertex2 = this->vertexes[id2];
    for(auto e : vertex1->edges)
        if(e->vertexes[1] == vertex2)
            return false;
    auto* newEdge1 = new Edge<TV, TE>(vertex1, vertex2, w);
    auto* newEdge2 = new Edge<TV, TE>(vertex2, vertex1, w);
    vertex1->edges.push_back(newEdge1);
    vertex2->edges.push_back(newEdge2);
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteVertex(string id) {
    if(!this->vertexes.count(id)){
        throw invalid_argument("Vertex was not deleted");
        return false;
    }
    for(Edge<TV, TE>* e : this->vertexes[id]->edges){
        Vertex<TV, TE>* vertex = e->vertexes[1];
        for(auto it = begin(vertex->edges); it != end(vertex->edges); ++it){
            if((*it)->vertexes[1] == this->vertexes[id]){
                (*it)->killSelf();
                vertex->edges.erase(it);
                break;
            }
        }
        e->killSelf();
    }
    this->vertexes[id]->killSelf();
    this->vertexes.erase(id);
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteEdge(string id) {
    int edges = 0;
    for(auto p : this->vertexes)  edges += p.second->edges.size();
    if (findById(id)) {
        for (auto i = this->vertexes[id]->edges.begin(); i != this->vertexes[id]->edges.end();) {
            if ((*i)->vertexes[1] == this->vertexes[id]) {
                this->vertexes[id]->edges.erase(i++);
                edges--;
            }
            else i++;
        }
        return true;
    }
    return false;
}

template<typename TV, typename TE>
TE &UnDirectedGraph<TV, TE>::operator()(string start, string end) {
    TV data_end;
    for(auto p:this->vertexes)
    {
        if(p.first==end)
            data_end = p.second->data;
    }

    for(auto p:this->vertexes)
    {
        if(p.first==start)
        {
            list<Edge<TV, TE>*> edge_temp = p.second->edges;
            for(auto itr:edge_temp)
            {
                if(itr->vertexes[1]->data==data_end)
                    return itr->weight;
            }
            throw invalid_argument("No existe esa arista");
        }
    }
}

template<typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density() {
    int edges = 0;
    for(auto p : this->vertexes)  edges += p.second->edges.size();
    return 2 * float(float(edges) / float((this->vertexes.size() * (this->vertexes.size() - 1))));
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold) {
    return density() >= threshold;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isConnected() {
    auto id = this->vertexes.begin()->first;
    unordered_map<TV, bool> visited;
    queue<Vertex<TV, TE>*> q;
    for (auto it : this->vertexes)
        visited[(it.second)->data] = false;

    visited[this->vertexes[id]->data] = true;

    q.push(this->vertexes[id]);
    auto u = q.front();
    q.push(u);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (auto it : u->edges) {
            if (visited[(it->vertexes)[1]->data] == false) {
                q.push((it->vertexes)[1]);
                visited[(it->vertexes)[1]->data] = true;
            }
        }
    }

    return all_of(visited.begin(), visited.end(), [](auto x) { return x.second; });

}

template <typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isStronglyConnected() throw() {
    throw invalid_argument("No aplica para Undirected Graph");
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::empty() {
    return (this->vertexes.size() == 0);
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::clear() {
    for (auto it_vertex: this->vertexes) {
        for (auto it_edge: (*it_vertex.second).edges) {
            (*it_edge).killSelf();
        }
        (*it_vertex.second).killSelf();
    }
    this->vertexes.clear();
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::displayVertex(string id) {
    cout << this->vertexes[id]->data << "-> ";
    for (auto const& j : this->vertexes[id]->edges) {
        cout << j->vertexes[1]->data << "(" << j->weight << ")" << " ";
    }
    cout << endl;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(string id) {
    if (this->vertexes.find(id) == this->vertexes.end())
        return false;
    return true;
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::display() {
    if(empty()){
        cout << "Empty Graph\n";
        return;
    }
    for(auto p : this->vertexes){
        cout << "ID: " << p.first << " | Vertex: (" << p.second->data << ") | Number of Edges: <" << p.second->edges.size() << ">:\n";
        for(auto it = begin(p.second->edges); it != end(p.second->edges); ++it)
            cout << "\t" << "Vertex " << (*it)->vertexes[1]->data << " ---> Weight (" << (*it)->weight << ")\n";
        cout << "\n";
    }
}

#endif // UNDIRECTEDGRAPH_H
