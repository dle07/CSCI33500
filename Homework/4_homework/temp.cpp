#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


void convertToLower(string& target){
    for( int i = 0; i < target.size(); i++){
        if( isalpha(target[i])){
            target[i] = tolower(target[i]);
        }
    }
}

int main(){
    string temp = "TSDAE'''DSDASDASDASD";
    convertToLower(temp);
    cout<<temp<<endl;
    /*
    while( getline(fs,currLine)){
        cout<<currLine<<" "<<currLine.size()<<endl;
    }
    /*
    fstream fs;
    fs.open("words.txt", ios :: in);
    if( fs.is_open()){
        string currLine;
        while( getline(fs,currLine))
            cout<<currLine<<endl;
    }
    fs.close();

    fs.open("wordsEnglish.txt", ios :: in);
    if( fs.is_open()){
        cout<<"Opening second file"<<endl;
        string currLine;
        while( getline(fs,currLine))
            cout<<currLine<<endl;
    }
    fs.close();
    */
    //wordsEnglish.txt
}