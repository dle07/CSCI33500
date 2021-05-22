// Daniel Le
// Main file for Part 2.3 of Homework 3.

#include "avl_tree.h"
#include "sequence_map.h"
// You will have to add #include "sequence_map.h"

#include <iostream>
#include <string>
using namespace std;

namespace {

// @dbx_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &dbx_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part 2.2
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
  cout<<"2:  "<<"Not Done"<<endl;
  cout<<"3a: "<<"Not Done"<<endl; 
  cout<<"3b: "<<"Not Done"<<endl; 
  cout<<"4a: "<<"Not Done"<<endl; 
  cout<<"4b: "<<"Not Done"<<endl; 
  cout<<"5a: "<<"Not Done"<<endl; 
  cout<<"5b: "<<"Not Done"<<endl; 
  cout<<"6a: "<<"Not Done"<<endl; 
  cout<<"6b: "<<"Not Done"<<endl; 
  cout<<"6c: "<<"Not Done"<<endl; 
  return 0;
}
