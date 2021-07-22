#include <iostream>
#include "Graph.h"
int main() {
    Graph graph;
    ifstream inputFile;
    string fileName;
    cout << "Please insert input file name" << endl;
    cin >> fileName;
    inputFile.open(fileName);
    if (!inputFile)
    {
        cout << "file error";
        exit(1);
    }
    if(!graph.readGraph(inputFile))
    {
        cout << "wrong input";
        exit(1);
    }
    inputFile.close();
//    cout<<"Graph edges:"<<endl;
//    graph.printGraph();
    Graph *H=graph.Algorithm(graph.getS(),graph.getT());
    cout<<"\nH edges: "<<endl;
    H->printGraph();
    // TESTING
    ofstream outputFile;
    outputFile.open("result.txt");
    if(outputFile)
        H->printToFile(outputFile);
    return 0;
}
