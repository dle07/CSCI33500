// Author: Daniel Le

#include "linear_probing.h"
#include "quadratic_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>   //std :: pair
#include <sstream>

using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {

  hash_table.MakeEmpty();  
  //..Insert your own code
    ifstream fs;
    stringstream ss;
    string currLine;
    string currWord;
    fs.open(words_filename); //open file and so we can insert them into the hash tables
    if( fs.is_open()){
        while( std :: getline(fs,currLine)){
            ss.clear();
            ss.str(currLine);
            while( ss >> currWord){
                hash_table.Insert(currWord);
            }
        }
        fs.close();
    }


  cout << "Number of items: " << hash_table.get_element_count() << endl;
  cout << "Size of hash table: " << hash_table.get_table_size() << endl;
  cout << "Load factor: " << hash_table.get_load_factor()<<endl;
  cout << "Average number of collisions: " << hash_table.get_average_collisions()<<endl;
  cout << "Total number of collisions: " <<  hash_table.get_total_collisions()<< endl;
  cout<<endl;
  fs.open(query_filename);
    if( fs.is_open()){
        std :: string currWord;
        std :: pair<bool,size_t> currPair;
        while(getline(fs, currLine)){
            ss.clear();
            ss.str(currLine);
            while(ss>> currWord){
                currPair = hash_table.search(currWord);
                if( currPair.first == true){
                    cout<<currWord<<" Found "<<currPair.second<<endl;
                }else{
                    cout<<currWord<<" Not_Found "<<currPair.second<<endl;
                }
            }
        }
        
    }
}

// namespace PROTECTED {

int testHashingWrapper(int argument_count, char **argument_list) {

    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 0;
    if (argument_count == 5) {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }
    
    if (param_flag == "linear") {
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename,
                         query_filename);
                         
    } else if (param_flag == "quadratic") {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename,
                                 query_filename);
    } else if (param_flag == "double") {
        
        cout << "r_value: " << R<<endl;
        HashTableDouble<string> double_probing_table;
        double_probing_table.SetR(R);
        TestFunctionForHashTable(double_probing_table, words_filename,
                                 query_filename);
                                 
    } else {
        cout << "Unknown hash type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

//};  // namespace PROTECTED

