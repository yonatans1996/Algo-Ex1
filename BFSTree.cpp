#include "BFSTree.h"

BFSTree::BFSTree(Graph graph, Vertex s) :_graph(graph), _s(s)
{
	BFS();
}

BFSTree::~BFSTree()
{
	delete[] _p;
	delete[] _d;
}

Vertex** BFSTree::GetParentArray()
{
	return _p;
}

int* BFSTree::GetDegreeArray()
{
	return _d; 
}

Graph BFSTree::GetGraph()
{
	return
		_graph;
}

//void BFSTree::BFS()    ////TODO ADD QUEUE!!!
//{
//	int numberOfVertices = _graph.GetNumberOfVertices();
//	
//	_d = new int[numberOfVertices];
//	_p = new Vertex* [numberOfVertices];
//	Vertex** L = new Vertex * [numberOfVertices];
//	Vertex* u, * v; // u in L. V in Adj(u)
//	Vertex* temp_vertex;
//	Vertex* temp_delete;
//
//	for (int i = 0; i < numberOfVertices; i++) // Init L and d
//	{
//		_d[i] = -1;
//		_p[i] = nullptr;
//		L[i] = nullptr;
//
//	}
//
//	// Level 0
//	L[0] = new Vertex(_s.value);
//	_d[_s.value - 1] = 0;
//
//
//	for (int i = 0; i < numberOfVertices; i++) // Loop builds L[i+1] from L[i]
//	{
//		u = L[i];
//		while (u != nullptr) // Run for Every u in L[i]
//		{
//			v = _graph.Adj(u->value);
//
//			while (v != nullptr) // Run for every v in Adj(u)
//			{
//				if (_d[v->value - 1] == -1)
//				{
//					_d[v->value - 1] = i + 1;
//					_p[v->value - 1] = new Vertex(i+1);
//
//					if (L[i + 1] == nullptr)
//					{
//						L[i + 1] = new Vertex(v->value);
//					}
//					else
//					{
//						temp_vertex = L[i + 1];
//						while (temp_vertex->next != nullptr) // insert vertex at the end of L[i+1]
//						{
//							temp_vertex = temp_vertex->next;
//						}
//						temp_vertex->next = new Vertex(v->value);
//					}
//				}
//				v = v->next;
//			}
//
//			temp_delete = u;
//			u = u->next;
//			delete temp_delete;
//		}
//	}
//	delete[]L;
//
//}

void BFSTree::BFS()
{
	int numberOfVertices = _graph.GetNumberOfVertices();

	_d = new int[numberOfVertices];
	_p = new Vertex * [numberOfVertices];
	
	Queue q;
	Vertex* u, * v; // u= Q.Deque() . v in Adj[u]

	for (int i = 0; i < numberOfVertices; i++) // Init d and parents
	{
		_d[i] = -1;
		_p[i] = nullptr;
	}

	q.EnQueue(new Vertex(_s.value));
	_d[_s.value - 1] = 0;

	while (!q.isEmpty())
	{
		u = q.DeQueue();
		v = _graph.Adj(u->value);

		while (v != nullptr) // for each V in Adj[u]
		{
			if (_d[v->value - 1] == -1)
			{
				_d[v->value - 1] = _d[u->value - 1] + 1;
				_p[v->value - 1] = new Vertex(u->value);

				q.EnQueue(new Vertex(v->value));
			}
			v = v->next;
		}
	}

}










void BFSTree::DeleteEdgesThatNotBetweenFollowedDegrees()
{
	Vertex* temp_vertex = nullptr;
	Vertex* temp_next;
	int numberOfVertices = _graph.GetNumberOfVertices();
	Vertex** adjacencyList = _graph.GetAdjacencyList();

	for (int i = 0; i < numberOfVertices; i++)
	{
		temp_vertex = adjacencyList[i];
		temp_next = temp_vertex;

		if (temp_next != nullptr)
		{
			temp_next = temp_vertex->next;
		}

		while (temp_vertex != nullptr)
		{
			if (_graph.isAdjacent(i + 1, temp_vertex->value) && !(_d[temp_vertex->value - 1] == _d[i] + 1))
			{
				_graph.removeEdge(i + 1, temp_vertex->value);
			}

			temp_vertex = temp_next;
			if (temp_next != nullptr)
			{
				temp_next = temp_next->next;
			}
		}
	}
}

void BFSTree::DeleteEdgesThatNotAccessibleFromT()
{
	Vertex* temp_vertex = nullptr;
	Vertex* temp_next;
	int numberOfVertices = _graph.GetNumberOfVertices();
	Vertex** adjacencyList = _graph.GetAdjacencyList();

	for (int i = 0; i < numberOfVertices; i++)
	{
		temp_vertex = adjacencyList[i];
		temp_next = temp_vertex;

		if (temp_vertex != nullptr)
		{
			temp_next = temp_vertex->next;
		}

		while (temp_vertex != nullptr)
		{
			if (_d[i] == -1)
			{
				_graph.removeEdge(i + 1, temp_vertex->value); // (i,u) degree is -1 so its not accessible from t
			}

			temp_vertex = temp_next;
			if (temp_next != nullptr)
			{
				temp_next = temp_next->next;
			}
		}
	}
}