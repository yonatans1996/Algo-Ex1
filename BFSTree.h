#include "Graph.h"
#include "Queue.h"

class BFSTree
{
	private:
		Graph _graph;
		Vertex _s;
		Vertex** _p;
		int* _d;

	public:
		BFSTree(Graph graph, Vertex s);
		~BFSTree();

		Vertex** GetParentArray();
		int* GetDegreeArray();
		Graph GetGraph();
		void BFS();
		void DeleteEdgesThatNotBetweenFollowedDegrees();
		void DeleteEdgesThatNotAccessibleFromT();
};