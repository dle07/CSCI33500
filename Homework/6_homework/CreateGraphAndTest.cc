// CSCI 335 Homework #6

// Your name: Daniel Le

#include <iostream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

int testGraphDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    string graphFile = argv[1];
    string adjacencyQueryFile = argv[2];

    Graph myGraph;
    myGraph.readGraphFile(graphFile);
    myGraph.testAdjacencies(adjacencyQueryFile);

    return 0;
}

// Do not modify anything below this line

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    testGraphDriver(argc, argv);

    return 0;
}
