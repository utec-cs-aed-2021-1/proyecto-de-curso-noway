#ifndef PARSER_HPP
#define PARSER_HPP

#include "nlohmann/json.hpp"
#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"
#include "helper_functs.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

// for convenience
using json = nlohmann::json;

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

Parser::Parser(string path_) {
    this->path = path_;
}

void Parser::clear() {
    this->path = "";
    this->jsonGraph.clear();
}

void Parser::readJSON() {
    ifstream file(this->path, ifstream::in);        // se abre el json en modo lectura
    string line, jsonString;
    while (getline(file, line))                     // se lee el json a una std::string
        jsonString += line + "\n";
    this->jsonGraph = json::parse(jsonString);            // se parsea a un objeto nlohmann::json
    cout << setw(4) << this->jsonGraph << endl;         // imprime el json bonito, con formato json
}

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

// la creación de edges será igual en los casos de ambos tipos de grafos, pues el método que se utiliza es
// pasar por los destinations de cada uno de los aeropuertos, generando un edge desde el aeropuerto actual
// hacia uno de sus posibles destinos


void Parser::dGraphMake(DirectedGraph<string, double> &tempGraph) {
    for (int i = 0; i < this->jsonGraph.size(); i++)
        tempGraph.insertVertex(this->jsonGraph[i]["Airport ID"], this->jsonGraph[i]["IATA/FAA"]);

    cout << findByAirportID(this->jsonGraph, "3797") << endl;
    for (int i = 0; i < this->jsonGraph.size(); i++) {
        for (int j = 0; j < this->jsonGraph[i]["destinations"].size(); j++) {
            tempGraph.createEdge(this->jsonGraph[i]["Airport ID"],
                                this->jsonGraph[i]["destinations"][j],
                                distance(this->jsonGraph[i]["Latitude"],
                                        this->jsonGraph[i]["Longitude"],
                                        this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["Latitude"],
                                        this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["Longitude"]));
        }
    }
}



#endif // PARSER_HPP
