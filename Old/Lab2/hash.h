#ifndef HASH_H
#define HASH_H

#include "LinkedList.h"
// #include<bits/stdc++.h> 

class hash 
{ 
private:
  int bucketSize;    // No. of buckets 
  
  // Pointer to an array containing buckets 
  LinkedList<int> *table; 

public: 
  hash(int size);  // Constructor 
  
  // inserts a key into hash table 
  void insertItem(int key); 
  
  // deletes a key from hash table 
  void deleteItem(int key); 
  
  // hash function to map values to key 
  int hashFunction(int x) { 
    return (x % BUCKET); 
  } 
  
  void displayHash(); 
}; 

#endif