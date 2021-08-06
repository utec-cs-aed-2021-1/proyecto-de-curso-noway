# Algoritmos y Estructura de Datos
## Proyecto sobre Grafos
--------

## Integrantes
- Eduardo Arróspide González

----
## Indicaciones
----
El proyecto del curso consiste en implementar una estructura de datos de grafo y un file parser. La estructura debe soportar los métodos y algoritmos descritos a continuacion:  


## Graph data structure

* El grafo debe ser dinámico (inserciones. eliminaciones, búsquedas, ...)
* Se debe implementar los dos tipos de grafos: dirigidos y no-dirigidos.
* No considerar loops ni multi-arista.


### Methods:
```cpp
bool insertVertex(string id, V data); // Creates a new vertex in the graph with some data and an ID

bool createEdge(string start, string end, E data); // Creates a new edge in the graph with some data

bool deleteVertex(string id); // Deletes a vertex in the graph

bool deleteEdge(string start, string end); // Deletes an edge in the graph, it is not possible to search by the edge value, since it can be repeated

E &operator()(string start, string end); // Gets the value of the edge from the start and end vertexes

float density() const; // Calculates the density of the graph

bool isDense(float threshold = 0.5) const; // Calculates the density of the graph, and determine if it is dense dependening on a threshold value

bool isConnected(); // Detect if the graph is connected

bool isStronglyConnected() throw(); // Detect if the graph is strongly connected (only for directed graphs)

bool empty(); // If the graph is empty

void clear(); // Clears the graph
```

### Algorithms:
```cpp
//Given the graph
UndirectedGraph<char, int> graph;

//1- Generates a MST graph using the Kruskal approach (only for undirected graphs)
Kruskal<char, int> kruskal(&graph);
UndirectedGraph<char, int> result = kruskal.apply();//return a tree

//2- Generates a MST graph using the Prim approach (only for undirected graphs)
Prim<char, int> prim(&graph, "A");
UndirectedGraph<char, int> result = prim.apply();//return a tree

//3- A *
AStar<char, int> astar(&graph, "A", "Z", vector<int> heuristics);
UndirectedGraph<char, int> result = astar.apply();

```


## JSON file parser
* Construye un grafo a partir de una archivo JSON de aereopuertos del mundo.


### Methods:
```cpp
void clear(); // Clears parser saved atributes

void readJSON(); // Parses JSON file and saves data into class
// NOTE: each derived class has its own readJSON method

void uGraphMake(UndirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph

void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
```
----
## Fin de indicaciones
----

## Grafos
Se utilizó la plantilla que fue brindada por el profesor para implementar los grafos, por lo que se usó una clase padre con métodos virtuales para ambos grafos, y se definieron los structs Vertex y Edge.

El constructor y destructor son estándar:
``` cpp
template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::UnDirectedGraph() = default;

template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::~UnDirectedGraph() {
    if (!this->vertexes.empty())
        clear();
}
```
#### Métodos:
##### Insert vertex
Primero, se comprueba que el vértice no exista ya en el grafo, utilizando el método findById(id) que será definido más adelante. Si el vértice que se desea agregar es nuevo, es asignado con el id especificado.
``` cpp
template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {
    if (!findById(id)) {
        auto* v = new Vertex<TV, TE>(vertex, id);
        this->vertexes[id] = v;
        return true;
    }
    return false;
}
```

##### Create Edge
Primero se comprueba que ambos vértices existen dentro del grafo, pues sin ellos no se podría crear una arista. Luego, se corrobora también que no se esté ingresando dos veces el mismo vértice, pues en estos grafos no se consideran loops. Finalmente, se crea la arista entre los dos vértices, a los cuales se accede mediante los ids ingresados, y se agrega la arista al vector edges que tiene cada vértice.

``` cpp
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
```
##### Delete vertex
Primero, se verifica, con unordered_map::count(), si el vértice que se desea eliminar existe en el grafo. Luego, se utiliza un doble for loop para eliminar las aristas del vértice y finalmente, el mismo vértice.
```cpp
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
```
##### Operator ()
El uso de este operador nos permitirá obtener el peso de una arista entre los vértices con un idstart y un id end.
```cpp
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
```

##### Density
Este método obtendrá la densidad del grafo, de acuerdo a lo visto en clases.
```cpp
template<typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density() {
    int edges = 0;
    for(auto p : this->vertexes)  edges += p.second->edges.size();
    return 2 * float(float(edges) / float((this->vertexes.size() * (this->vertexes.size() - 1))));
}
```

##### Is Dense
Este método, por su parte, definirá si es que el grafo es denso o no, utilizando el método ansiedad y un threshold que será pasado como argumento.
```cpp
template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold) {
    return density() >= threshold;
}
```

##### Is Connected
De forma bastante estándar, este método verificará si el grafo es conexo o no, utilizando un unordered_map para marcar los vértices ya visitados y una queue para ir pasando los vértices.
```cpp
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
```

##### Empty
Este sencillo método retornará un booleano que determinará si el grafo está vacío o no.
``` cpp
template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::empty() {
    return (this->vertexes.size() == 0);
}
```

##### Clear
Iterando a través de cada arista de cada vértice del grafo, este método vaciará el grafo.
```cpp
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
```

##### Display Vertex
Imprimirá de forma amigable el vértice seleccionado a través de su id, y los ejes con los que tiene una arista y sus pesos.
```cpp
template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::displayVertex(string id) {
    cout << this->vertexes[id]->data << "-> ";
    for (auto const& j : this->vertexes[id]->edges) {
        cout << j->vertexes[1]->data << "(" << j->weight << ")" << " ";
    }
    cout << endl;
}
```
##### Find By ID
Retornará un booleano que determinará si el vértice pasado a través de su id existe en el grafo.
```cpp
template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(string id) {
    if (this->vertexes.find(id) == this->vertexes.end())
        return false;
    return true;
}
```

##### Display
Finalmente, esta función de display imprimirá el grafo de la siguiente forma:
![Display](Display.png "Display")
```cpp
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
```

----
## Parser
Se utilizó la librería [nlohmann::json](https://github.com/nlohmann/json), la cual nos permite parsear archivos json como si fuesen un tipo de dato básico del STL. Súper útil.

Clase Parser:
```cpp
class Parser
{
private:
    string path;                // ruta del archivo
    json jsonGraph;             // objeto nlohmann::json que almacena el json
                                // como estructura primaria
public:
    Parser(string path_);

    void clear(); // Clears parser saved atributes

    void readJSON(); // Parses JSON file and saves data into class
    // NOTE: each derived class has its own readJSON method

    void uGraphMake(UnDirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph

    void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
};
```
El constructor y su primer método, clear, son bastante estándar.
```cpp
Parser::Parser(string path_) {
    this->path = path_;
}

void Parser::clear() {
    this->path = "";
    this->jsonGraph.clear();
}
```

Para el método readJSON(), se tuvieron que hacer varios ajustes.
```cpp
void Parser::readJSON() {
    ifstream file(this->path, ifstream::in);        // se abre el json en modo lectura
    string line, jsonString;
    while (getline(file, line))                     // se lee el json a una std::string
        jsonString += line + "\n";
    this->jsonGraph = json::parse(jsonString);            // se parsea a un objeto nlohmann::json
}
```
Los archivos json de los aeropuertos estaban rodeados por corchetes "[]", lo cual complicaba el parseo directo a un objeto nlohmann::json. Luego de muchas pruebas, se descubrió que, si se pasaba el json a un string normal de C++ primero, y luego recién se parseaba a un objeto nlohmann::json, no había problema.
Si se agrega, al final del método, la siguiente línea de código: ```cout << setw(4) << this->jsonGraph << endl;```, se puede observar en consola una impresión de la data parseada como si estuviese en formato json, de la siguiente manera:
![](ImpresionJSON.png)


Luego, los métodos uGraphMake() y dGraphMake() son iguales, solo que retornan grafos no dirigidos y dirigidos, respectivamente.
```cpp
void Parser::uGraphMake(UnDirectedGraph<string, double> &tempGraph) {
    for (int i = 0; i < this->jsonGraph.size(); i++)
        tempGraph.insertVertex(this->jsonGraph[i]["Airport ID"], this->jsonGraph[i]["IATA/FAA"]);   // se crean primero los vértices

    for (int i = 0; i < this->jsonGraph.size(); i++) {                          // doble loop para crear los Edges desde
        for (int j = 0; j < this->jsonGraph[i]["destinations"].size(); j++) {   // cada destination de cada aeropuerto
            tempGraph.createEdge(this->jsonGraph[i]["Airport ID"],             // primer atributo de createEdge
                                this->jsonGraph[i]["destinations"][j],         // segundo atributo de createEdge
                                distance(this->jsonGraph[i]["Latitude"],       // funcion distance como tercer atributo de createEdge
                                        this->jsonGraph[i]["Longitude"],
                                        this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["Latitude"],
                                        this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["Longitude"]
                                    )
                                );
        }
    }
}
```
Para cada vértice, se utiliza el Airport ID como id, y el código IATA/FAA como data. Para la creación de las aristas, se utiliza una función distance(), que utilizará fórmulas reales para calcular distancias realistas entre dos latitudes y longitudes. Esta función, junto a otras, es implementada en el archivo helper_functs.hpp:
```cpp
#ifndef HELPER_FUNCTS_HPP
#define HELPER_FUNCTS_HPP

#include "nlohmann/json.hpp"
#include <cmath>
#define pi 3.14159265358979323846
using namespace std;

// for convenience
using json = nlohmann::json;

/////////////////////////////////////////////////////////////////////
/////////////////// Funciones de ayuda /////////////////////////////

// para convertir longitudes y latitudes a radianes
long double toRadians(const long double grados)
{
    long double grado = (pi) / 180;
    return (grado * grados);
}

//para calcular la distancia entre dos latitudes y longitudes

long double distance(string lat1, string long1, string lat2, string long2)
{
    long double lat_1 = stoi(lat1);
    long double long_1 = stoi(long1);           // se convierten las latitudes y longitudes
    long double lat_2 = stoi(lat2);             // a long doubles para calcular la distancia
    long double long_2 = stoi(long2);

    lat_1 = toRadians(lat_1);
    long_1 = toRadians(long_1);           // Se convierten las latitudes
    lat_2 = toRadians(lat_2);             // y longitudes a radianes
    long_2 = toRadians(long_2);

    // Haversine Formula
    long double dlong = long_2 - long_1;
    long double dlat = lat_2 - lat_1;

    long double ans = pow(sin(dlat / 2), 2) + cos(lat_1) * cos(lat_2) * pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));


    long double R = 6371; // Radio de la Tierra en KM

    ans = ans * R;

    return ans;
}

// funcion para encontrar la ubicación de un aeropuerto en el jsonGraph teniendo como base el AirportID

int findByAirportID(json jsonGraph, string id) {
    for (int i = 0; i < jsonGraph.size(); i++) {
        if (jsonGraph[i]["Airport ID"] == id)
            return i;
    }
    return 215;                              // si no existe el destino, se fijará Nueva York como destino
}

#endif // HELPER_FUNCTS_HPP
```
La función findByAirportID() permite encontrar el index de un aeropuerto utilizando solo el Airport ID. Se busca conseguir esto pues en los objetos nlohmann::json, se puede utilizar el operador [] para acceder a cada aeropuerto. En esta función, además, para prevenir errores de data en los archivos json, retornará el index 215 (correspondiente al aeropuerto de Nueva York) si es que el Airport ID buscado no existe.
Se eliminaron manualmente los aeropuertos de AirportID 5562, 5674 y 5675, ya que en las latitudes tenían letras, por lo que se consideró como data corrupta.
Además, se eliminó el aeropuerto de AirportID 1104, pues su única destination era hacia uno de los aeropuertos previamente mencionados.
