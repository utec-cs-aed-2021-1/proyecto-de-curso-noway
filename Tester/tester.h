#ifndef PROYECTO_DE_CURSO_NOWAY_TESTER_H
#define PROYECTO_DE_CURSO_NOWAY_TESTER_H

#include "../Graph/DirectedGraph.h"
#include "../Graph/UndirectedGraph.h"
#include "../Parser/parser.hpp"
#include <string>
#include <iostream>

//using namespace rapidjson;
using namespace std;

struct Tester {
    static void executeExamples();
    static void executeParserPeru();
    static void executeParserInternational();
};

void Tester::executeExamples() {
    cout << "Directed Graph: " << endl;

    DirectedGraph<char, int> graph1;
    graph1.insertVertex("1", 'A');
    graph1.insertVertex("2", 'B');
    graph1.insertVertex("3", 'C');
    graph1.insertVertex("4", 'D');
    graph1.insertVertex("5", 'E');

    graph1.createEdge("1", "2", 10);
    graph1.createEdge("1", "3", 5);
    graph1.createEdge("3", "4", 15);
    graph1.createEdge("2", "4", 20);
    graph1.createEdge("1", "4", 12);
    graph1.createEdge("2", "5", 25);
    graph1.createEdge("4", "5", 30);
    graph1.createEdge("5", "1", 30);

    graph1.display();
    cout << endl;
    cout << "Density: " << graph1.density() << endl;

    cout << "Is the graph dense? ";
    if (graph1.isDense(0.6)) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Is the graph connected? ";
    if (graph1.isConnected()) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Is vertex 3 on the graph? ";
    if (graph1.findById("3")) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Vertex 3: ";
    graph1.displayVertex("3");

    cout << endl;

    cout << "Undirected Graph: " << endl;

    UnDirectedGraph<char, int> graph2;
    graph2.insertVertex("1", 'A');
    graph2.insertVertex("2", 'B');
    graph2.insertVertex("3", 'C');
    graph2.insertVertex("4", 'D');
    graph2.insertVertex("5", 'E');

    graph2.createEdge("1", "2", 10);
    graph2.createEdge("1", "3", 5);
    graph2.createEdge("3", "4", 15);
    graph2.createEdge("2", "4", 20);
    graph2.createEdge("1", "4", 12);
    graph2.createEdge("2", "5", 25);
    graph2.createEdge("4", "5", 30);

    graph2.display();
    cout << endl;
    cout << "Density: " << graph2.density() << endl;

    cout << "Is the graph dense? ";
    if (graph2.isDense(0.6)) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Is the graph connected? ";
    if (graph2.isConnected()) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Is vertex 5 on the graph? ";
    if (graph2.findById("5")) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Vertex 5: ";
    graph2.displayVertex("5");

    cout << endl;
}

void Tester::executeParserPeru() {
    Parser Peru("Parser/Data/pe.json");
    Peru.readJSON();
    UnDirectedGraph<string, double> uGraph;

    Peru.uGraphMake(uGraph);
    uGraph.display();
}

void Tester::executeParserInternational() {
    Parser graph("Parser/Data/airports.json");
    graph.readJSON();
    DirectedGraph<string, double> dGraph;

    graph.dGraphMake(dGraph);
    for (int i = 0; i < 10; i++)
        cout << graph.jsonGraph[i] << endl;
    dGraph.display();
}


#endif //PROYECTO_DE_CURSO_NOWAY_TESTER_H
