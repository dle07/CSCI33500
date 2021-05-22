// Daniel Le
/*

*/
// Main file for Part 2.2 of Homework 3.

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"
#include <cmath>  //log2() function
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

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

template <typename TreeType>
void QueryTree(const string &dbx_filename, TreeType &a_tree) {
  // Code for running Part 2.1

  string db_line;
  fstream file_stream(dbx_filename, ios :: in);  //create a object of fstream so we can process the data, since we are reading, the second paramter is in
  if( file_stream.is_open() ){
      while( getline(file_stream, db_line) ){
        if(db_line.empty()) continue; //to avoid processing empty lines
        vector<string> temp = parseLine(db_line);
        if(temp.empty()){  // vector is empty, invalid line no sequence!!!
          continue;
        }
        string enzyme_acroynonym = temp[0];  //get the enzyme acronym
        for( int i = 1; i < temp.size(); i++){  // from index 1 to end are the recoginition sequence
          SequenceMap tempMap = SequenceMap(temp[i], enzyme_acroynonym);
          if(tempMap.empty() == false){
            a_tree.insert(tempMap);
          }
        }

      }
  }
}


// @dbx_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &dbx_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part 2.2
  
  //Part 1
  QueryTree(dbx_filename,a_tree);

  //Part 2
  cout<<"2: "<<a_tree.getNodeCount()<<endl;

  //Part 3
  cout<<"3a: "<<a_tree.getAverageDepth()<<endl;
  cout<<"3b: "<<a_tree.getDepthToLogRatio()<<endl;

  //Part 4
  pair<int,float> part_four_data = a_tree.getStepFourData(seq_filename);
  cout<<"4a: "<<part_four_data.first <<endl;
  cout<<"4b: "<<part_four_data.second<<endl;

  //Part 5
  pair<int,float> part_five_data = a_tree.getStepFiveData(seq_filename);
  cout<<"5a: "<<part_five_data.first<<endl;
  cout<<"5b: "<<part_five_data.second<<endl;
  
  //Part 6
  cout<<"6a: "<<a_tree.getNodeCount()<<endl;
  cout<<"6b: "<<a_tree.getAverageDepth()<<endl;
  cout<<"6c: "<<a_tree.getDepthToLogRatio()<<endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << dbx_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(dbx_filename, seq_filename, a_tree);
  return 0;
}





