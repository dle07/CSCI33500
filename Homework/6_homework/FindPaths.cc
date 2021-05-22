// CSCI 335 Homework #6

// Your name: Daniel Le
 

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "graph.h"

using namespace std;

int findPathDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    Graph graph;
    string graphFile = argv[1];
    string intString = argv[2];
    int  startVertex = stoi(intString);

    graph.readGraphFile(graphFile);
    graph.findPaths(startVertex);

    return 0;
}

// Do not modify anything below this line

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    findPathDriver(argc, argv);

    return 0;
}
