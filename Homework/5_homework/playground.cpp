#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>


void print(vector<int>& input){
    for( auto el : input){
        cout<<el<<" ";
    }
    cout<<endl;
}
using namespace std;

int main(){
    vector<int> temp = {1,6,7,7,5,4,4,5,3,11,12,16};
    vector<int> temp1 = temp;
    vector<int> temp2 = temp;
    vector<int> temp3 = temp;
    vector<int> temp4 = temp;
    //insertionSort(temp,0, temp.size()-1 , std :: less<int>{});
    quicksort(temp,0, temp.size()-1 , std :: less<int>{});
    print(temp);

    //insertionSort(temp1,0, temp.size()-1 , std :: greater<int>{});
    quicksort(temp1, 0, temp1.size()- 1,std :: greater<int>{} );
    print(temp1);
    /*
    cout<<endl;

    
    QuickSort2(temp1,std :: greater<int>{});
    for( int el : temp1)cout<<el<<" ";
    cout<<endl;
    /*
    for( int el : temp2 ) cout<<el<<" ";

    */

}