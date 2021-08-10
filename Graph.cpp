#pragma once
#include "Graph.h"
#include "BFSTree.h"

Graph::Graph() :_adjacency_list(nullptr), _number_of_vertices(0), _t(0), _s(0) {}

Graph::Graph(const Graph& other)
{
	makeEmptyGraph(other._number_of_vertices);

	_t = other._t;
	_s = other._s;

	Vertex* current_vertex;

	for (int i = 0; i < _number_of_vertices; i++)
	{
		current_vertex = other._adjacency_list[i];

		while (current_vertex != nullptr)
		{
			AddEdge(i + 1, current_vertex->value);
			current_vertex = current_vertex->next;
		}
	}
}

void Graph::makeEmptyGraph(int n)
{
	_adjacency_list = new Vertex * [n];
	_number_of_vertices = n;

	for (int i = 0; i < n; i++)
	{
		_adjacency_list[i] = nullptr;
	}
}

bool Graph::isAdjacent(int v, int u)
{
	if (!checkIfVertexExist(u) || !checkIfVertexExist(v))	//// Check vertex's are valid
	{
		return false;
	}

	Vertex* temp_vertex = _adjacency_list[v - 1];

	while (temp_vertex != nullptr)
	{
		if (temp_vertex->value == u)
		{
			return true;
		}

		temp_vertex = temp_vertex->next;
	}

	return false;
}

bool Graph::addEdge(int u, int v)       /// check if edge exist
{
	if (!checkIfVertexExist(u) || !checkIfVertexExist(v))   // Check vertex's are valid
	{
		return false;
	}

	Vertex* neighbor_list_of_u = _adjacency_list[u - 1];

	if (neighbor_list_of_u == nullptr)		//// v is u's first neighbor.
	{
		_adjacency_list[u - 1] = new Vertex(v);
	}
	else	//// insert edge to the end of the list
	{
		while (neighbor_list_of_u->next != nullptr)
		{
			neighbor_list_of_u = neighbor_list_of_u->next;
		}

		neighbor_list_of_u->next = new Vertex(v);
	}

	return true;
}

bool Graph::removeEdge(int u, int v)
{
	if (!isAdjacent(u, v))
	{
		return false;
	}

	Vertex* temp_vertex = _adjacency_list[u - 1];

	if (temp_vertex->value == v)	//// need to remove from list head
	{
		_adjacency_list[u - 1] = _adjacency_list[u - 1]->next;
		delete temp_vertex;
	}
	else	//// need to remove edge from list
	{
		while (temp_vertex != nullptr && temp_vertex->next->value != v)		//// find v edge. or stop when list ends
		{
			temp_vertex = temp_vertex->next;
		}

		Vertex* temp_delete = temp_vertex->next; // temp_delete hold edge to remove
		temp_vertex->next = temp_vertex->next->next;
		delete temp_delete;
	}
	return true;
}

Graph::~Graph() {

	Vertex* temp_vertex;
	Vertex* temp_delete;

	for (int i = 0; i < _number_of_vertices; i++)
	{
		temp_vertex = _adjacency_list[i];
		
		while (temp_vertex != nullptr)
		{
			temp_delete = temp_vertex;
			temp_vertex = temp_vertex->next;
			delete temp_delete;
		}
	}

	delete[]_adjacency_list;
}

void Graph::PrintGraph()
{
	Vertex* temp_vertex;

	for (int i = 0; i < _number_of_vertices; i++)
	{
		temp_vertex = _adjacency_list[i];

		while (temp_vertex != nullptr)
		{
			cout << i + 1 << " " << temp_vertex->value << endl;
			temp_vertex = temp_vertex->next;
		}
	}
}

int Graph::isEmpty()
{
	return _number_of_vertices > 0 ? 1 : 0;
}

int Graph::AddEdge(int i, int j)
{
	bool flag = addEdge(i, j);
	return flag ? 1 : 0;
}

Vertex* Graph::Adj(int i)
{
	if (!checkIfVertexExist(i))
	{
		return nullptr;
	}

	return _adjacency_list[i - 1];
}

bool Graph::checkIfVertexExist(int x)
{
	return !(x > _number_of_vertices || x < 1);
}

Graph* Graph::transposeGraph()
{
	Graph* tGraph = new Graph();
	tGraph->makeEmptyGraph(_number_of_vertices);
	Vertex* temp_vertex;

	for (int i = 0; i < _number_of_vertices; i++)
	{
		temp_vertex = _adjacency_list[i];

		while (temp_vertex != nullptr)
		{
			tGraph->AddEdge(temp_vertex->value, i + 1);
			temp_vertex = temp_vertex->next;
		}
	}

	return tGraph;
}

Graph* Graph::Algorithm(int s, int t)
{
	BFSTree bfsTreeOfG(*this, s);     /// BFS on G.
	bfsTreeOfG.DeleteEdgesThatNotBetweenFollowedDegrees();   /// bfsTreeOfG now holding Gs graph.

	Graph* G_s_Transpose = (bfsTreeOfG.GetGraph()).transposeGraph();     /// transpose Gs.

	BFSTree bfsTreeOfGsTranspose(*G_s_Transpose, t);    /// BFS on Gs-transpose.
	bfsTreeOfGsTranspose.DeleteEdgesThatNotAccessibleFromT();     /// bfsTreeOfGsTranspose now holding H-transpose.

	Graph* H = bfsTreeOfGsTranspose.GetGraph().transposeGraph();      ///  transpose H-transpose

	delete G_s_Transpose;
	return H;
}

int Graph::getNumberBetweenWhiteSpaces(char& o_lastChar) ///betweenWS
{
	char currentChar;
	int currentNumber = 0;

	currentChar = getchar();

	while (isWhiteSpace(currentChar))   //// skip white spaces
	{
		currentChar = getchar();
	}

	if (!isNumber(currentChar))   /// if char is not white space or number - exit program
	{
	
		exitProgram();
	}

	while (isNumber(currentChar))   /// get number
	{
		currentNumber = currentNumber * 10 + currentChar - '0';
		currentChar = getchar();
	}

	if ( (!cin.eof()) && (!isWhiteSpace(currentChar))&& !isEOF(currentChar))   ///if not ws or eof - exit program.
	{
		exitProgram();
	}

	o_lastChar = currentChar;
	return currentNumber;
}

//void Graph::ReadGraph()
//{
//	char currentChar;
//	int firstVertex, secondVertex;
//
//	_number_of_vertices = getNumberBetweenWhiteSpaces(currentChar);
//	makeEmptyGraph(_number_of_vertices);
//
//	///check if endoffile.
//	_s = getNumberBetweenWhiteSpaces(currentChar);
//	_t = getNumberBetweenWhiteSpaces(currentChar);
//
//	if (!checkIfVertexExist(_s) || !checkIfVertexExist(_t)) // Check s and t are good values
//	{
//		exitProgram();
//	}
//
//	while (!cin.eof() && !isEOF(currentChar))
//	{
//		firstVertex = getNumberBetweenWhiteSpaces(currentChar);
//		secondVertex= getNumberBetweenWhiteSpaces(currentChar);
//		
//		if (!addEdge(firstVertex, secondVertex)) // if edge isn't valid return false
//		{
//			exitProgram();
//		}
//	}
//}

void Graph::ReadGraph() {
	int current_input;
	int u, v;
	cin >> current_input; // Get n

	if (current_input < 0 || !cin.good() || cin.eof()) // check n is good value
		exitProgram();
	makeEmptyGraph(current_input);
	cin >> _s;
	
	cin >> _t;
	if (cin.eof() || !cin.good() || !checkIfVertexExist(_s) || !checkIfVertexExist(_t)) // Check s and t are good values
		exitProgram();
	cin >> u;
	
	while (cin.good() && !cin.eof() && u!=0)
	{
		
		cin >> v;
		
		if (!cin.good() || !addEdge(u, v)) // if edge isn't valid return false
			exitProgram();
		cin >> u;
	
	}

}



//void Graph::ReadGraph()
//{
//	char currentChar;
//	int firstVertex, secondVertex;
//	cin >> _number_of_vertices;
//	if (cin.eof() || !cin.good())
//		exitProgram();
//	_number_of_vertices = getNumberBetweenWhiteSpaces(currentChar);
//	makeEmptyGraph(_number_of_vertices);
//
//	///check if endoffile.
//	_s = getNumberBetweenWhiteSpaces(currentChar);
//	_t = getNumberBetweenWhiteSpaces(currentChar);
//
//	
//	if (!checkIfVertexExist(_s) || !checkIfVertexExist(_t)) // Check s and t are good values
//	{
//		exitProgram();
//	}
//
//	while (!cin.eof() && !isEOF(currentChar))
//	{
//		firstVertex = getNumberBetweenWhiteSpaces(currentChar);
//		secondVertex = getNumberBetweenWhiteSpaces(currentChar);
//
//		if (!cin.eof() && !isEOF(currentChar))
//			if (!addEdge(firstVertex, secondVertex)) // if edge isn't valid return false
//			{
//				exitProgram();
//			}
//	}
//}






bool Graph::isNumber(char ch)
{
	return !(ch < '0' || ch > '9');
}

bool Graph::isWhiteSpace(char ch)
{
	return (ch == ' ' || ch == '\n');
}

bool Graph::isEOF(char ch)
{
	return (ch == '\x1a' || ch == EOF);
}

void Graph::exitProgram()
{
	cout << "invalid input";
	exit(1);
}

Graph* Graph::RunAlgorithmWithTiming(int s, int t)
{

	auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);

	Graph* H = Algorithm(s, t);
	
	auto end = chrono::high_resolution_clock::now();
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	cout << "Time taken by function Algorithm is : " << fixed
		<< time_taken << setprecision(9);
	cout << " sec" << endl;
	
	return H;
}