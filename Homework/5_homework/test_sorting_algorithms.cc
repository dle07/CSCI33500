// Homework 5
// Testing Sorting Algorithms
// Daniel Le

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.

void TestingTiming() {
  cout << "Testing Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();    
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  vector<int> result;
  for( size_t i = 0; i < size_of_vector; i++){
    result.push_back(rand());
  }
  // Use rand() to generate random integer
  // Add code

  return result;

}

// Generate and returns sorted vector of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  // Add code
  vector<int> result;
  if( smaller_to_larger){
      for( int i = 1; i <= size_of_vector; i++){
        result.push_back(i);
      }
  }else{
      for( int i = size_of_vector; i>= 1; i--){
        result.push_back(i);
      }
  }
  return result;
}

// Verifies that a vector is sorted given a comparator
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
  // Add code
  for( int i = 0; i < input.size()-1;i++){
        if( less_than(input[i], input[i + 1])) continue;
        else if( input[i] == input[i+1]) continue;
        return false;
    }

    return true;
}
//cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
// Computes duration given a start time and a stop time in nano seconds
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time) {
  // Add code
  return chrono:: duration_cast<chrono::nanoseconds>(end_time - start_time).count();
  
}
template <typename comparator>
void getInformation(vector<int> & input_vector, chrono::high_resolution_clock::time_point &start_time, chrono::high_resolution_clock::time_point &end_time, comparator less_than){
    cout<<"Runtime: "<<ComputeDuration(start_time,end_time)<<" ns"<<endl;
    cout<<"Verified: ";
    if( VerifyOrder(input_vector, less_than)){
       cout<<"1"<<endl;
    }
    else{ cout <<"0"<<endl; }
    cout<<endl;
}

// Wrapper function to test the different sorting algorithms
int testSortingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    return 0;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return 0;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return 0;
  }
  
  // This block of code to be removed for your final submission.
  //TestingTiming();

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  cout<<endl;
  vector<int> input_vector;
  vector<int> tempVector;
  if (input_type == "random") {
    // Generate random vector
    input_vector = GenerateRandomVector(input_size);
    
  } else {
    // Generate sorted vector.
    if( input_type == "sorted_small_to_large"){
      input_vector = GenerateSortedVector(input_size, true );
    }else{
      input_vector = GenerateSortedVector(input_size, false);
    }
  }
  tempVector = input_vector;
  
  // Call quicksort / heapsort / mergesort using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ...
  if( comparison_type == "less"){

    input_vector = tempVector;
    cout<<"HeapSort"<<endl;
    auto begin = chrono :: high_resolution_clock :: now();
    HeapSort(input_vector, std :: less<int>{});
    auto end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: less<int>{});

    input_vector = tempVector;
    cout<<"MergeSort"<<endl;
    begin = chrono :: high_resolution_clock :: now();
    MergeSort(input_vector, std :: less<int>{});
    end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: less<int>{});

    input_vector = tempVector;
    cout<<"QuickSort"<<endl;
    begin = chrono :: high_resolution_clock :: now();
    QuickSort(input_vector, std :: less<int>{});
    end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: less<int>{});

  }else{
    
    input_vector = tempVector;
    cout<<"HeapSort"<<endl;
    auto begin = chrono :: high_resolution_clock :: now();
    HeapSort(input_vector, std :: greater<int>{});
    auto end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: greater<int>{});


    input_vector = tempVector;
    cout<<"MergeSort"<<endl;
    begin = chrono :: high_resolution_clock :: now();
    MergeSort(input_vector, std :: greater<int>{});
    end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: greater<int>{});

    input_vector = tempVector;
    cout<<"QuickSort"<<endl;    
    begin = chrono :: high_resolution_clock :: now();
    QuickSort(input_vector, std :: greater<int>{});
    end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: greater<int>{});

  }

  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...

  cout<<"Testing Quicksort Pivot Implementations"<<endl<<endl;

    if( comparison_type == "less" ){
    
    input_vector = tempVector;
    cout<<"Median of Three"<<endl<<endl;
    auto begin = chrono :: high_resolution_clock :: now();
    QuickSort(input_vector, std :: less<int>{});
    auto end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: less<int>{});

    input_vector = tempVector;
    cout<<"Middle"<<endl<<endl;
    begin = chrono :: high_resolution_clock :: now();
    QuickSort2(input_vector, std :: less<int>{});
    end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: less<int>{});


    input_vector = tempVector;
    cout<<"First"<<endl<<endl;
    begin = chrono :: high_resolution_clock :: now();
    QuickSort3(input_vector, std :: less<int>{});
    end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: less<int>{});

    }else{
    
    input_vector = tempVector;
    cout<<"Median of Three"<<endl<<endl;
    auto begin = chrono :: high_resolution_clock :: now();
    QuickSort(input_vector, std :: greater<int>{});
    auto end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: greater<int>{});

    input_vector = tempVector;
    cout<<"Middle"<<endl<<endl;
    begin = chrono :: high_resolution_clock :: now();
    QuickSort2(input_vector, std :: greater<int>{});
    end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: greater<int>{});

    input_vector = tempVector;
    cout<<"First"<<endl<<endl;
    begin = chrono :: high_resolution_clock :: now();
    QuickSort3(input_vector, std :: greater<int>{});
    end = chrono :: high_resolution_clock :: now();
    getInformation(input_vector, begin, end, std :: greater<int>{});

    }

  return 1;
}

// Do not change anything below

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  testSortingWrapper(argc, argv);

  return 0;
}
