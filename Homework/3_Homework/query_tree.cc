// Daniel Le
// Main file for Part 2.1 of Homework 3.

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream> //Dependency to process a text file
#include <vector>
#include <unordered_set>  //Used for testing purposes only.
using namespace std;


unordered_set<string> mySet;

namespace {


vector<string> parseLine(string &db_line ){ //helper function to seperate process the data and return the data in a the form of a vector
  db_line.pop_back(); //removes the extra /
  vector<string> result;        //Let's use a two pointer apporach, everytime we see a / it means we've encountered a new word, we should use substr, and append it to the vector
                            // AarI/CACCTGCNNNN'NNNN/'NNNNNNNNGCAGGTG//
  int i = 0;  //pointer to mark the left side 
  int j = 0;  //faster runner pointer
  while( j < db_line.size()){
    if(db_line[j] == '/'){  //
      result.push_back( db_line.substr(i, j-i) );  //push the word onto the vector
      i = j + 1; //mark the new potential word
    }
    ++j; //increment the right pointer
  }
  return result;
}

// @dbx_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &dbx_filename, TreeType &a_tree) {
  // Code for running Part 2.1

  string db_line;
  fstream file_stream(dbx_filename, ios :: in);  //create a object of fstream so we can process the data, since we are reading, the second paramter is in
  cout<<dbx_filename<<endl;


  if( file_stream.is_open() ){

      while( getline(file_stream, db_line) ){
        if(db_line.empty()) continue; //to avoid processing empty lines
        vector<string> temp = parseLine(db_line);
        if(temp.empty()) continue;           // vector is empty, invalid line no sequence!!

        string enzyme_acroynonym = temp[0];  //get the enzyme acronym
        for( int i = 1; i < temp.size(); i++){  // from index 1 to end are the recoginition sequence
          mySet.insert(temp[i]);
          SequenceMap tempMap = SequenceMap(temp[i], enzyme_acroynonym); 
          a_tree.insert(tempMap);
        }
        
      }
  }
  file_stream.close();
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  
  AvlTree<SequenceMap> a_tree;
  QueryTree(dbx_filename, a_tree);

  string tempSequence;
  while( cin>> tempSequence){
    if(tempSequence.empty()) continue;
    SequenceMap tempMap(tempSequence,"");
    a_tree.partOneFind(tempMap);
  }
  return 0;
  
}
