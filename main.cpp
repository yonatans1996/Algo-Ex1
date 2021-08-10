#include <iostream>
#include "Graph.h"

int main()
{	
	Graph graph;
	graph.ReadGraph();
	
	Graph* H = graph.RunAlgorithmWithTiming(graph.getS(), graph.getT());
	
	H->PrintGraph();

	return 0;
}
