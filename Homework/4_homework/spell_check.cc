// Author : Daniel Le

#include "quadratic_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void convertToLower(string& target){
    for( size_t i = 0; i < target.size(); i++){
        if( isalpha(target[i])){
            target[i] = tolower(target[i]);
        }
    }
}
string removePunctuation(string & curr){
    string res;
    int start = 0;
    int end = curr.size()-1;
    while( !isalpha(curr[start] ) ){
        start++;
    }
    while(!isalpha(curr[end])) {
        end--;
    }
    res = curr.substr(start,end-start + 1);
    return res;
}
//
vector<string> testA(HashTableDouble<string>& dictionary, string inputWord){
    vector<string> result;
    string currTemp;
    for( size_t i = 0; i<= inputWord.size(); i++){
        for( int j = 25; j >=0 ; j--){
            currTemp = inputWord;
            currTemp.insert(i,string(1, char('z'- j) ));
            if( dictionary.Contains(currTemp)){
                result.push_back(currTemp);
            }
        }
    }
    return result;
}
vector<string> testB(HashTableDouble<string>& dictionary, string current){
    vector<string> result;
    string currTemp;
    for( size_t i = 0; i < current.size(); i++){
        currTemp = current;
        currTemp.erase(i,1);
        if( dictionary.Contains(currTemp)){
            result.push_back(currTemp);
        }
    }

    return result;
}
vector<string> testC(HashTableDouble<string>& dictionary, string current){
    vector<string> result;
    for( size_t i = 0; i < current.size(); i++){
        for( size_t j = i + 1; j < current.size(); j++){
            swap(current[i], current[j]);
            if( dictionary.Contains(current)){
                result.push_back(current);
            }
            swap(current[i], current[j]);
        }
        
    }
    return result;
}

HashTableDouble<string> MakeDictionary(const string & dictionary_filename){
    HashTableDouble<string> result;
    int r = 97;
    result.SetR(r);
    fstream fs;
    string currLine;
    string currWord;
    stringstream ss;

    fs.open(dictionary_filename, ios::in);
    if(fs.is_open()){
        while(getline(fs,currLine)){
            ss.clear();
            ss.str(currLine);
            while( ss >> currWord){
                result.Insert(currWord);
            }
        }
    }
    fs.close();

    return result;
}

void SpellChecker(HashTableDouble<string>& dictionary,const string &document_filename){
    
    fstream fs;
    string currLine;
    string currWord;
    
    fs.open(document_filename, ios::in);
    if( fs.is_open()){

        while(getline(fs,currLine)){
            stringstream ss(currLine);
            while( ss >> currWord){
                currWord = removePunctuation(currWord); //removes punctuation
                convertToLower(currWord);
                if(dictionary.Contains(currWord)){
                    cout<<currWord<<" is CORRECT"<<endl;
                }else{
                    vector<string> currSet;
                    //Testing A
                    currSet = testA(dictionary, currWord);
                    for( auto elem : currSet){ cout<<"*** "<<currWord<<" -> "<<elem<<" *** "<<"case A"<<endl; }
                    //Testing B
                    currSet = testB(dictionary,currWord);
                    for( auto elem : currSet){ cout<<"*** "<<currWord<<" -> "<<elem<<" *** "<<"case B"<<endl; }
                    //Testing C
                    currSet = testC(dictionary,currWord);
                    for( auto elem : currSet){ cout<<"*** "<<currWord<<" -> "<<elem<<" *** "<<"case C"<<endl; }
                }
            }
        }
    }
}

int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

     //Call functions implementing the assignment requirements.
     HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
     SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
             << endl;
        return 0;
    }

    testSpellingWrapper(argc, argv);

    return 0;
}
