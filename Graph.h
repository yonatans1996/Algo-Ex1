#pragma once

#include "Vertex.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;

class Graph 
{
	public:

		Graph();	//// CTOR
		Graph(const Graph& other);    //// Copy Ctor
		~Graph();

		void makeEmptyGraph(int n);		          // Init Graph with n vertex
		bool isAdjacent(int v, int u);		       // Return True if v-u is edge in the graph. else return false
		bool addEdge(int u, int v);		          // Add edge (u,v) to the Graph. Return True if insert success
		bool removeEdge(int u, int v);		      // Remove edge and return true if edge removed successfully.
		void ReadGraph();		 // build Graph from file. return True if success
		bool checkIfVertexExist(int x);		      // Return true if x is a valid number. else return false
		void PrintGraph();		                  // print the graph
		int isEmpty();			                  // return 1 if we have 0 vertex. else return 0
		int AddEdge(int i, int j);		         // insert edge (i,j). return 1 if success. else return 0
		int getT() { return _t; }
		int getS() { return _s; }
		Vertex* Adj(int i);		                  // return the neighbors list of vertex i
		Graph* Algorithm(int s, int t);			 // Main algorithm on Vertex s as start. Vertex t is the final vertex in the path
		int GetNumberOfVertices() { return _number_of_vertices; }
		Vertex** GetAdjacencyList() { return _adjacency_list; }
		Graph* RunAlgorithmWithTiming(int s, int t);


	private:
		//Functions
		Graph* transposeGraph();                     // Return transpose graph
		bool isNumber(char ch);
		bool isWhiteSpace(char ch);
		int getNumberBetweenWhiteSpaces(char& lastChar);
		void exitProgram();
		bool isEOF(char ch);

		//Members
		Vertex** _adjacency_list = nullptr;
		int _number_of_vertices = 0;
		int _s;
		int _t;

};