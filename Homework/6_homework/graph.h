#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct EdgeFromStart{
    int vertex;
    double distanceFromStart;

    EdgeFromStart(){
        this -> vertex = 0;
        this -> distanceFromStart = 0;
    }
    EdgeFromStart(int vertex, double distanceFromStart){
        this->vertex = vertex;
        this-> distanceFromStart = distanceFromStart;
    }

    bool operator < (  const EdgeFromStart & compared) const {
        return this-> distanceFromStart < compared.distanceFromStart;
    }

    bool operator > (EdgeFromStart compared){
        return this-> distanceFromStart >  compared.distanceFromStart;
    }


};



//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements
//Author : Daniel Le

//Directed Graph
//-1 will represent infinity
class Graph{
    private:
    int vertexCount; //number of vertices in our graph;

    vector<vector<pair<int, double>>> data;   // Adjacency Matrix graph representation 
    vector<double> costResults;
    vector<int> previousVertex;
    vector<bool> visited;
    BinaryHeap<EdgeFromStart> heap;


    

    public:
    int getVertexCount(){
        return this-> vertexCount;
    }
    void printAllVectorSizes(){
        cout<<"data size: "<<data.size()<<endl;
        cout<<"costResults size: "<<costResults.size()<<endl;
        cout<<"previousVertex size: "<<previousVertex.size()<<endl;
        cout<<"visited size: "<<visited.size()<<endl;

    }

    void findPaths(int startVertex){
        this -> djikstras(startVertex);
        string path;
        int tempIndex;
        for( int i = 1 ; i <= vertexCount ; i++){
            if( costResults[i] == -1){  //No possible path from start
                cout<<i<<": not_possible"<<endl;
            }else{

                path.clear();
                tempIndex = i;
                path+= to_string(tempIndex);

                while(tempIndex != startVertex){
                    tempIndex = previousVertex[tempIndex];
                    path += " " + to_string(tempIndex);
                }
                reverse(path.begin(),path.end());
                cout<<i<<": "<<path<<" cost: "<<std::fixed<< std::setprecision(1) <<costResults[i]<<endl;
            }
        }

    }
    //Visited here meas that the nextVertex has been already relaxed. It's not possible to relax more than once, so just continue;
    //Current Node will be the min vertex from the heap
    //Iterate all connecting nodes from the currentNode, relax connecting nodes
    //For every relaxation append a new pair of that vertex and the cost from start into the heap
    void djikstras( int startingVertex){
        int currentVertex;
        double currentDistance;

        int nextV;
        int nextCost;

        visited[startingVertex] = true;
        costResults[startingVertex] = 0;

        previousVertex[startingVertex] = startingVertex;

        heap.insert(EdgeFromStart(startingVertex, 0.0));

        while( !heap.isEmpty()){
            currentVertex = heap.findMin().vertex;
            currentDistance = heap.findMin().distanceFromStart;
            heap.deleteMin();
            visited[currentVertex] = true;

            for(auto nextVertex: data[currentVertex]){
                nextV = nextVertex.first;
                nextCost = nextVertex.second + currentDistance;

                if( visited[nextV]) continue; //IF it's already relaxed, then continue
                else if(costResults[nextV] == -1){
                    costResults[nextV] =  nextCost;
                    previousVertex[nextV] = currentVertex;
                    heap.insert(EdgeFromStart(nextV, nextCost));
                    continue;
                }else if(costResults[nextV] <  nextCost){
                    continue;    
                }else if( costResults[nextV] > nextCost){  // checks to see if we can relax
                    previousVertex[nextV] = currentVertex;
                    costResults[nextV] = nextCost;
                    heap.insert(EdgeFromStart(nextV,nextCost));
                }
            }
        }

    }

    void testAdjacencies(string & adjacencyFileName){
        int startVertex;
        int endVertex;
        fstream fs;
        fs.open(adjacencyFileName, ios :: in);
        bool found = false;
        double weight;
        if(fs.is_open()){
            while( fs>> startVertex){
                fs >> endVertex;
                cout<<startVertex<<" "<<endVertex<<": ";
                found = false;
                for( auto el : data[startVertex] ){
                    if( el.first == endVertex){
                        found = true;
                        weight = el.second;
                        break;
                    }
                }
                if( found ){
                    cout<< "connected "<<weight<<endl;
                }else{
                    cout<< "not_connected"<<endl;
                }
            
            }
        }

        fs.close();
    }

    void printGraph(){
        for( int i = 0; i < data.size(); i++){
            cout<<i<<"  :";
            for( auto & el : data[i]){
                cout<<el.first<<" "<<el.second<<" ";
            }
            cout<<endl;
        }
    }
    
    void readGraphFile( string & graphFile){
        fstream fs;
        fs.open(graphFile, ios::in);
        stringstream ss;
        string currentString;

        int currIndex;
        int currInt;
        double currFloat;

        if(fs.is_open()){
            ss.clear();
            getline( fs, currentString);
            ss.str(currentString);
            ss >> currInt;
            this -> vertexCount = currInt;

            this -> data = vector<vector<pair<int,double>>> (this-> vertexCount + 1, vector<pair<int,double>>());
            ss.clear();
            while( getline(fs,currentString)){
                ss.clear();
                ss.str(currentString);
                ss >> currIndex;
                while( ss >> currInt){
                    //cout<<currInt<<" ";
                    ss >> currFloat;
                    //cout<<currFloat<<" ";
                    this -> data[currIndex].push_back(make_pair(currInt,currFloat));
                }                
            }
        }
        this-> visited = vector<bool>(this-> vertexCount + 1, false);
        this-> costResults = vector<double>(this-> vertexCount + 1, -1);   // -1 will represent infinity
        this-> previousVertex = vector<int> (this-> vertexCount + 1, -1);  //-1 means that it was unreachable, this graph is unnconncted

        fs.close();
    }

};



#endif 
