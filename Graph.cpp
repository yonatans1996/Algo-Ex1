#include "Graph.h"
Graph::Graph():graph_arr(nullptr),_vertex_size(0),_t(0),_s(0){}
Graph::Graph(const Graph &other)
{
    makeEmptyGraph(other._vertex_size);
    _t=other._t;
    _s=other._s;
    Vertex *temp_vertex;
    for(int i=0;i<_vertex_size;i++)
    {
        temp_vertex=other.graph_arr[i];
        while(temp_vertex!= nullptr)
        {
            addEdge(i+1,temp_vertex->value);
            temp_vertex=temp_vertex->next;
        }
    }
}
void Graph::makeEmptyGraph(int n) {
    graph_arr=new Vertex *[n];
    _vertex_size=n;
    for(int i=0;i<n;i++)
        graph_arr[i]= nullptr;
}

bool Graph::isAdjacent(int v, int u) {
    if( !checkValidVertex(u) || !checkValidVertex(v)) // Check vertex's are valid
        return false;
    Vertex *temp_vertex=graph_arr[v-1];
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
    Vertex *temp_vertex=graph_arr[u-1];
    if(temp_vertex== nullptr) // first edge for vertex u
    {
        graph_arr[u-1]=new Vertex(v,c);
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
    Vertex *temp_vertex=graph_arr[u-1];
    if(temp_vertex==nullptr) // edge not exists
        return false;
    if(temp_vertex->value==v) // need to remove from list head
    {
        graph_arr[u-1]=graph_arr[u-1]->next;
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
    return true;
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

bool Graph::readGraph( ifstream& inputFile) {
    int current_input;
    int u,v;
    inputFile >> current_input; // Get n
    if(current_input<0 || !inputFile.good()) // check n is good value
        return false;
    makeEmptyGraph(current_input);
    inputFile >> _s;
    inputFile >> _t;
    if(!checkValidVertex(_s) || !checkValidVertex(_t)  || !inputFile.good()) // Check s and t are good values
        return false;
    int test=0;
    while (!inputFile.eof() )
    {
        inputFile >> u;
        inputFile >> v;
        if(!addEdge(u,v)) // if edge isn't valid return false
            return false;
        test++;
    }


    return true;
}

void Graph::printGraph() {
    Vertex *temp_vertex;
    for(int i=0;i<_vertex_size;i++)
    {
        temp_vertex=graph_arr[i];
        while(temp_vertex!= nullptr)
        {
            cout<<"("<<i+1<<","<<temp_vertex->value<<"), ";
            temp_vertex=temp_vertex->next;
        }
    }

}

int Graph::isEmpty() {
    return _vertex_size>0?1:0;
}

int Graph::addEdge(int i, int j) {
    bool flag=addEdge(i,j,-1); // -1 weight if no weight assigned
    return flag?1:0;
}

Vertex *Graph::adj(int i) {
    if(!checkValidVertex(i))
        return nullptr;
    return graph_arr[i-1];
}

bool Graph::checkValidVertex(int x) {
    return !(x > _vertex_size || x < 1);
}

Graph* Graph::transposeGraph() {
    Graph *tGraph=new Graph();
    tGraph->makeEmptyGraph(_vertex_size);
    Vertex *temp_vertex;
    for (int i=0;i<_vertex_size;i++)
    {
        temp_vertex=graph_arr[i];
        while(temp_vertex!=nullptr)
        {
            tGraph->addEdge(temp_vertex->value,i+1,temp_vertex->weight);
            temp_vertex=temp_vertex->next;
        }
    }
    return tGraph;
}
int *Graph::buildDegreeFromBFS(int s) {
    int *d=new int[_vertex_size]; // Degree array
    Vertex **L=new Vertex *[_vertex_size];
    Vertex *u,*v; // u in L. V in Adj(u)
    Vertex *temp_vertex;
    Vertex *temp_delete;
    for(int i=0;i<_vertex_size;i++) // Init L and d
    {
        d[i]=-1;
        L[i]=nullptr;
    }
    // Level 0
    L[0]=new Vertex(s,-1);
    d[s-1]=0;
    for(int i=0;i<_vertex_size;i++) // Loop builds L[i+1] from L[i]
    {
        u=L[i];
        while(u!= nullptr) // Run for Every u in L[i]
        {
            v=adj(u->value);
            while(v!=nullptr) // Run for every v in Adj(u)
            {
                if(d[v->value-1]==-1)
                {
                    d[v->value-1]=i+1;
                    if(L[i+1]==nullptr)
                        L[i+1]=new Vertex(v->value,-1);
                    else
                    {
                        temp_vertex=L[i+1];
                        while(temp_vertex->next!=nullptr) // insert vertex at the end of L[i+1]
                            temp_vertex=temp_vertex->next;
                        temp_vertex->next=new Vertex(v->value,-1);
                    }
                }
                v=v->next;
            }
            temp_delete=u;
            u=u->next;
            delete temp_delete;
        }
    }
    delete []L;
    return d;
}

Graph *Graph::Algorithm(int s, int t) {
    int *d=buildDegreeFromBFS(s); // BFS on s
    Graph *G_s=new Graph(*this);
    Vertex *temp_vertex = nullptr;
    Vertex *temp_next;
    for(int i=0;i<_vertex_size;i++)
    {
        temp_vertex=G_s->graph_arr[i];
        temp_next=temp_vertex;
        if(temp_next!=nullptr)
            temp_next=temp_vertex->next;
        while(temp_vertex!=nullptr) {
            if (G_s->isAdjacent(i+1,temp_vertex->value) && !(d[temp_vertex->value - 1] == d[i]+1) )
            {
                G_s->removeEdge(i+1, temp_vertex->value);
            }

            temp_vertex = temp_next;
            if(temp_next!= nullptr)
                temp_next=temp_next->next;
        }
    }
    Graph *G_s_Transpose=G_s->transposeGraph();
    delete []d;
    d=G_s_Transpose->buildDegreeFromBFS(t); // BFS on t
    for(int i=0;i<_vertex_size;i++)
    {

        temp_vertex=G_s_Transpose->graph_arr[i];
        temp_next=temp_vertex;
        if(temp_vertex!=nullptr)
            temp_next=temp_vertex->next;
        while(temp_vertex!=nullptr)
        {
            if(d[i]==-1)
            {
                G_s_Transpose->removeEdge(i+1,temp_vertex->value); // (i,u) degree is -1 so its not accessible from t
            }
            temp_vertex=temp_next;
            if(temp_next!=nullptr)
                temp_next=temp_next->next;
        }
    }
    Graph *H=G_s_Transpose->transposeGraph(); // G_s now is H
    delete G_s;
    delete G_s_Transpose;
    return H;
}

void Graph::printToFile(ofstream &outputFile) {
    Vertex *temp_vertex;
    bool flag=false; // Dont print \n on first line
    for(int i=0;i<_vertex_size;i++)
    {
        temp_vertex=graph_arr[i];
        while(temp_vertex!= nullptr)
        {
            if(flag)
                outputFile<<"\n";
            outputFile<<i+1<<" "<<temp_vertex->value;
            temp_vertex=temp_vertex->next;
            flag=true;
        }
    }
}



