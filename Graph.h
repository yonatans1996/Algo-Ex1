#pragma once
#include "Vertex.h"
class Graph{
public:
    void makeEmptyGraph(int n); // Init Graph with n vertex
    bool isAdjacent(int v, int u); // Return True if v-u is edge in the graph. else return false
    bool addEdge(int u, int v, int c); // Add edge (u,v) with weight c to the Graph. Return True if insert success
    bool removeEdge(int u, int v); // Remove edge and return true if edge removed successfully.
    explicit Graph(int n){makeEmptyGraph(n);}; // CTOR with n vertex to init
    ~Graph();
    bool readGraph(); // build Graph from file. return True if success
    void printGraph(); // print the graph
    int isEmpty(); // return 1 if we have 0 vertex. else return 0
    int addEdge(int i, int j); // insert edge (i,j). return 1 if success. else return 0
    Vertex * adj(int i); // return the neighbors list of vertex i
    bool checkValidVertex(int x); // Return true if x is a valid number. else return false

private:
    Vertex **graph_arr= nullptr; // List of neighbors
    int _vertex_size=0;

};

