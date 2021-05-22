// --> Author : Daniel Le
// This class simmulates a sequence of pairs. The pairs are meant to be of the type integer, float, or double.
// There are several custom functions included in this class such as adding two sequences, and outputting the stream in a nice format to the terminal
// This class supports the big five described in our class textbook.

#ifndef CSCI335_HOMEWORK2_POINTS2D_H_
#define CSCI335_HOMEWORK2_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>


namespace teaching_project {
// Place comments that provide a brief explanation of this class,
// and its sample usage.
template<typename Object>
class Points2D {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation for it.

  // Zero-parameter constructor. 
  // Set size to 0.

  // The big five are the destructor, assignment operator, copy constructor, move constructor, and the move assignment operator
  Points2D(){
    this->size_ = 0; //No arguement constructor, sets size to 0
  }

  // Copy-constructor. This is a deep copy
  Points2D(const Points2D &rhs){  //Copy constructor is called when a newly created instance uses a already existing object to create the object
    int rhsSize = rhs.size();  //Set the size appropriately
    this -> size_ = rhsSize;
    this -> sequence_ = new std :: array<Object,2>[rhsSize]; //Pointer to an array of array<Object,2> of the same size of the rhs Points2D.
    for(int i = 0; i < rhsSize; i++){
      this->sequence_[i][0] = rhs.sequence_[i][0];    //Loops over the sequence of rhs and copies the data
      this->sequence_[i][1] = rhs.sequence_[i][1];
    }

  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2D copy = rhs; 
  // std::swap(*this, copy);
  // return *this;
  // }
  Points2D& operator=(const Points2D &rhs){  //Copy assignment is used on already intitialized objects
    Points2D tempCopy = rhs;  //Creates a deep copy of the rhs object
    std :: swap(*this,tempCopy); //Swaps our current object with the deep copy
    return *this;
  }

  // Move-constructor. 
  /*
    The move constructor simply repoints the current fields to the paramater's fields. This saves operations by not having to create a deep copy and reassigning
  */
  Points2D(Points2D &&rhs){
      this->sequence_ = rhs.sequence_;  //Redirects
      this->size_ = rhs.size_;
      rhs.sequence_ = nullptr;  //Makes it null
      rhs.size_ = 0;         //Set's size to 0 appropriately for rhs
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2D& operator=(Points2D &&rhs){
    std :: swap(this->size_,rhs.size_ );      //Swaps which effectively reassigns member fields
    std :: swap (this->sequence_, rhs.sequence_);
    return *this;
  }
  
  ~Points2D(){
    delete[] sequence_; //Free up the whole dynamic array of array<Object,2>, these deletes the whole array, no need to loop
  }

  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item) {
    // Provide code.
    this->size_ = 1;        // one item means size of 1
    this-> sequence_ = new std :: array<Object,2>[1];  // creates the dynamic array appropriately of size 1
    this-> sequence_[0] = item;   //assigns the first element
    
  }

  

  // Read a chain from standard input.
  void ReadPoints2D() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;  //Gets the first integer from the stream so we can appropriately allocate the fields and size
    // Allocate space for sequence.
    // Add code here.
    if( this->size_ > 0)delete[] sequence_;
    this->size_ =  size_of_sequence;
    //delete[] sequence_; //delete current sequence
    this->sequence_ = new std :: array<Object,2>[this ->size_];

    Object token;
    
    for (int i = 0 ;input_stream >> token; ++i) { //If you think about it, there are i/2 pairs, thus i/2 gives us the index of the sequence we're inserting
      // Read coordinates.
      // Fill sequence_ here.
      if(i % 2 == 0){  //This is even, this means we should place it in the 0th index
        this -> sequence_[i/2][0] = token;
      }else{    //This mean's this is odd, place it in the array of the first index
        this -> sequence_[i/2][1] = token;
      }
    }
    
  }

  size_t size() const {
    return this->size_;
  }

  // @location: an index to a location in the given sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std :: array<Object, 2>& operator[](size_t location) const { 
    if( location >= this->size_) abort();      // if the size is outside the range then abort, no need to check for negative because the index is of type size_t, it's always non-negative
    return sequence_[location];
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2D operator+(const Points2D &c1, const Points2D &c2) {  //Friend so we can access private members
   
   size_t finalSize;
   if( c1.size() >  c2.size()) finalSize = c1.size();  //What should the size of the output Points2D be? It should be the size of the largest sequence of the input given the problem instruction
   else{ finalSize = c2.size();}

   int i = 0;
   int j = 0;
   Points2D result;
   result.sequence_ = new std :: array<Object,2>[finalSize];
   result.size_ = finalSize;

   while( i < c1.size() && j < c2.size()){  //We can only add if the two pointers are valid, if they're valid we add each of the respective values and write the elements in our resultant object

      result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[j][0]; //The logic here is simmilar to merging arrays
      result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[j][1];
      i++;
      j++;
   }
   //From here, at MOST only one of these loops will execute. This occurs when the size of both sequences aren't equal to eachother. We simply continue onwards until the pointers are invalid and overwrite the data in our result object
   //Case where c2.size() < c1.size()
   while( i < c1.size()){
      result.sequence_[i][0] = c1.sequence_[i][0];
      result.sequence_[i][1] = c1.sequence_[i][1];
      ++i;
   }
    //Case where size c1.size() < c2.size()
   while( j < c2.size()){
      result.sequence_[j][0] = c2.sequence_[j][0];
      result.sequence_[j][1] = c2.sequence_[j][1];
     ++j;
   }


   return result;

 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2d) {

    if(some_points2d.size() == 0){  //edge case, simply add the string "()" to the output stream
      out<<"()";
    }else{
      for( int i = 0; i < some_points2d.size(); i++){
      out<<"("<<some_points2d[i][0]<<", "<<some_points2d[i][1]<<")"<<" ";  //For each point we first add open parentheses to the stream,
                    // then the x field value of the current cordinate pair, then comma,then space, then y value componenent of the cordinate pair,
                    //then the closing parentheses then space because thats what the output format wants
      }

    }
    out<< std :: endl;   //adds end line to the output stream
   return out;  //return output stream

   
  }
 
 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of the sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK2_POINTS2D_H_
