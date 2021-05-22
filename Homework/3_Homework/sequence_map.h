#ifndef SEQUENCE_MAP
#define SEQUENCE_MAP

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
Author : Daniel Le

*/

//Big five : Destructor, Copy Constructor, Move constructor, Copy assignment operator = , Move assignment operator=
class SequenceMap{

    private:
    string recognition_sequence_ ;
    vector<string> enzyme_acronyms_;

    public:
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro){// As per the assignment documentation, the vector will only contain one element, the second paramater
        this -> recognition_sequence_ = a_rec_seq;
        this -> enzyme_acronyms_.push_back(an_enz_acro);
    }; 
    
    bool operator<(const SequenceMap &rhs) const{
        return (this->recognition_sequence_ < rhs.recognition_sequence_);
    };
    // << Operator Overloading
    friend ostream & operator<< ( ostream & out, const SequenceMap& input){
        for( string el: input.enzyme_acronyms_){
            out<<el<<" ";
        }
        out<<endl;
        return out;
    }
    
    void Merge(const SequenceMap &other_sequence){
        for( string el: other_sequence.enzyme_acronyms_){
            this->enzyme_acronyms_.push_back(el);
        }
    }
    void print(){
        cout<<"Recognition Sequence:"<< recognition_sequence_<<" "<< enzyme_acronyms_[0];
    }

    string &getRecognitionSequence(){
        return this-> recognition_sequence_;
    }
    bool empty(){
        return recognition_sequence_.empty() || enzyme_acronyms_.empty();
    }
    //Big-Five using = default notation as documentation says it's okay to
    //Simmilar implementation for default is used by our class textbook
    ~SequenceMap () {};
    SequenceMap ( const SequenceMap & input) = default;  //copy
    SequenceMap (SequenceMap && input) = default; //move
    SequenceMap& operator = (SequenceMap && input) = default;  //copy assignment
    SequenceMap& operator = (const SequenceMap & input) = default; //move assignment


    




};

#endif