#include "Graph.h"

void Graph::makeEmptyGraph(int n) {
    graph_arr=new Vertex *[n];
    _vertex_size=n;
    for(int i=0;i<n;i++)
        graph_arr[i]= nullptr;
}

bool Graph::isAdjacent(int v, int u) {
    if( !checkValidVertex(u) || !checkValidVertex(v)) // Check vertex's are valid
        return false;
    Vertex *temp_vertex=graph_arr[v+1];
    while(temp_vertex!= nullptr)
    {
        if(temp_vertex->value==u)
            return true;
        temp_vertex=temp_vertex->next;
    }
    return false;
}

bool Graph::addEdge(int u, int v, int c) {
    if( !checkValidVertex(u) || !checkValidVertex(v)) // Check vertex's are valid
        return false;
    Vertex *temp_vertex=graph_arr[u+1];
    if(temp_vertex== nullptr) // first edge for vertex u
    {
        graph_arr[u+1]=new Vertex(v,c);
    }
    else // insert edge on list
    {
        while(temp_vertex->next!= nullptr)
        {
            temp_vertex=temp_vertex->next;
        }
        temp_vertex->next=new Vertex(v,c);
    }
    return true;
}

bool Graph::removeEdge(int u, int v) {
    if( !checkValidVertex(u) || !checkValidVertex(v)) // Check vertex's are valid
        return false;
    Vertex *temp_vertex=graph_arr[u+1];
    if(temp_vertex==nullptr) // edge not exists
        return false;
    if(temp_vertex->value==v) // need to remove from list head
    {
        graph_arr[u+1]=graph_arr[u+1]->next;
        delete temp_vertex;
    }
    else{ // need to remove edge from list
        while( temp_vertex != nullptr && temp_vertex->next->value!=v) // find v edge. or stop when list ends
            temp_vertex=temp_vertex->next;
        if(temp_vertex == nullptr)
            return false; // edge not exists.
        Vertex *temp_delete=temp_vertex->next; // temp_delete hold edge to remove
        temp_vertex->next=temp_vertex->next->next;
        delete temp_delete;
    }
}

Graph::~Graph() {
    Vertex *temp_vertex;
    Vertex *temp_delete;
    for(int i=0;i<_vertex_size;i++)
    {
        temp_vertex=graph_arr[i];
        while(temp_vertex!= nullptr)
        {
            temp_delete=temp_vertex;
            temp_vertex=temp_vertex->next;
            delete temp_delete;
        }
    }
    delete []graph_arr;
}

bool Graph::readGraph() {
    return false;
}

void Graph::printGraph() {

}

int Graph::isEmpty() {
    return _vertex_size>0?1:0;
}

int Graph::addEdge(int i, int j) {
    return 0;
}

Vertex *Graph::adj(int i) {
    if(!checkValidVertex(i))
        return nullptr;
    return graph_arr[i+1];
}

bool Graph::checkValidVertex(int x) {
    return !(x > _vertex_size || x < 1);
}

