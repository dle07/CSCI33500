#ifndef DOUBLE_HASHING_
#define DOUBLE_HASHING_
//Author : Daniel Le
// For testing the double hashing table, please use an R value of 97
// R = 97
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include "quadratic_probing.h"
using namespace std;

// Double Hashing 
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};
    void SetR(int & Rvalue){
      this-> R = Rvalue;
    }

    size_t getRValue(){ return this-> R; }
    size_t get_element_count(){ return this->current_size_; }
    size_t get_table_size(){ return this->array_.size(); }
    float get_load_factor(){  // element_count / table_size
        return float(this->current_size_) / this->array_.size();}
    float get_average_collisions(){
        return float(this-> collisons) / this->current_size_;
    }
    size_t get_total_collisions(){return this->collisons;}

    std :: pair<bool, size_t> search(HashedObj & target){
        std :: pair<bool,size_t> result;
        bool contains = false;
        size_t probes = 1;
        size_t offset = 1;
        size_t current_pos = InternalHash(target);
        size_t initialTemp = current_pos;

        
        // probe = hash(x) + i*hash2(x) % array_.size()
        while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != target) {
          probes++;   //increment prbes by one because we are advancing
          current_pos  = (initialTemp + (offset * InternalHash2(target)))% array_.size();
          offset++;
        }
        

        if( !IsActive(current_pos) ) contains = false;
        else if( IsActive(current_pos) && this -> array_[current_pos].element_ == target ) contains = true;

        result.first = contains;
        result.second = probes;
        return result;

  }
  
  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
  { MakeEmpty(); }
  bool Contains(const HashedObj & x)  {
    return IsActive(FindPos(x));
  }
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }
  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5  
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }
  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    
  std::vector<HashEntry> array_;
  int R = 97;
  size_t current_size_ = 0;
  mutable size_t collisons = 0;


  bool IsActive(size_t current_pos) 
  { return array_[current_pos].info_ == ACTIVE; }
  //h1(x) InternalHash    h'(x) =  ( h(x) + i * h2(x) )% array_.size()
  size_t FindPos(const HashedObj & x)  {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
    
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
      this->collisons++;
      current_pos  = (current_pos + (offset* InternalHash2(x))) % array_.size();
      offset++;
    }
    return current_pos;
  }
  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));  //new size is atleast twice the size
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }

  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size();
  }
  
    // hash2(x) = R - (x mod R)
  size_t InternalHash2(const HashedObj & x){   
    static std::hash<HashedObj> hf;
    return size_t(this -> R - (hf(x) % this-> R) ) ;
  }
};



#endif