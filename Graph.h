#pragma once
#include "Vertex.h"
#include <iostream>
#include <fstream>
using namespace std;
class Graph{
public:
    //CTOR
    Graph(); // CTOR
    Graph(const Graph &other); // Copy Ctor
    ~Graph();
    void makeEmptyGraph(int n); // Init Graph with n vertex
    bool isAdjacent(int v, int u); // Return True if v-u is edge in the graph. else return false
    bool addEdge(int u, int v, int c); // Add edge (u,v) with weight c to the Graph. Return True if insert success
    bool removeEdge(int u, int v); // Remove edge and return true if edge removed successfully.
    bool readGraph( ifstream& inputFile); // build Graph from file. return True if success
    bool checkValidVertex(int x); // Return true if x is a valid number. else return false
    void printGraph(); // print the graph
    int isEmpty(); // return 1 if we have 0 vertex. else return 0
    int addEdge(int i, int j); // insert edge (i,j). return 1 if success. else return 0
    int getT(){return _t;}
    int getS(){return _s;}
    Vertex * adj(int i); // return the neighbors list of vertex i
    Graph *Algorithm(int s, int t); // Main algorithm on Vertex s as start. Vertex t is the final vertex in the path
    void printToFile(ofstream &outputFile); // Print H graph to file
private:
    //Functions
    Graph *transposeGraph(); // Return transpose graph
    int * buildDegreeFromBFS(int s); // Build degree array from BFS on vertex s
    //Members
    Vertex **graph_arr= nullptr; // List of neighbors
    int _vertex_size=0;
    int _s; // first vertex
    int _t; // last vertex

};

