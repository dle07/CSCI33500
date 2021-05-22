#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include "graph.h"



using namespace std;

int main(){

    Graph testGraph;    

    string graphFile = "Graph2.txt";
    int startVertex = 1;

    testGraph.readGraphFile(graphFile);
    //testGraph.printGraph();
    //cout<<"vertex count: "<<testGraph.getVertexCount()<<endl;
    //testGraph.printAllVectorSizes();
    testGraph.findPaths(startVertex);


    /*
    fstream fs;

    string temp = "Graph1.txt";
    /*
    BinaryHeap<EdgeFromStart> testHeap;
    vector<int> vec1 =      {1,  2,    3,    4,  5,   6,   7,   8,   9,   10};
    vector<double> vec2 =   {.8, 11.1, 11.0, 12, 5.4, 5.4, 5.3, 5.6, 70,  3.55};

    for( int i = 0; i < vec1.size(); i ++){
        EdgeFromStart input(vec1[i],vec2[i]);
        testHeap.insert(input);
    }
    int count = 0;
    while( !testHeap.isEmpty()){
        EdgeFromStart target = testHeap.findMin();
        cout<<target.vertex<<"    :"<<target.distanceFromStart<<endl;
        testHeap.deleteMin();
        count++;
    }
    cout<<"COUNT       :"<<count<<endl;
    
    
    /*
    fs.open("Graph1.txt", ios :: in);
    string currLine;
    stringstream ss("12 12");

    int curr;
    ss>>curr;
    cout<<curr<<endl;
    vector<vector<pair<int,float>>> data;
    data = vector<vector<pair<int,float>>> (curr + 1, vector<pair<int,float>>());
    cout<<"hello"<<endl;
    /*
    getline(fs,currLine);
    cout<<currLine<<endl;

    if( fs.is_open()){
        while( getline(fs, currLine)){
            cout<<currLine<<endl;
        }
        
    }

    */
    /*
    Graph graph;
    string temp1 = "AdjacencyQueries1.txt";

    graph.readGraphFile(temp);
    graph.printGraph();
    cout<<endl;
    cout<<"TESTING ADJACENCIES       :"<<endl;
    graph.testAdjacencies(temp1);
    cout<<endl;

    */
    
}