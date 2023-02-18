#include "hash.h"

hash::hash(int size) 
{ 
  this->bucketSize = size; 
  table = new LinkedList<int>[bucketSize]; 
} 
  
void hash::insertItem(int key) 
{ 
  int index = hashFunction(key); 
  // I need to fix this part
  // table[index].push_back(key);  
} 
  
void hash::deleteItem(int key) 
{ 
  // get the hash index of key 
  int index = hashFunction(key); 
  
  // find the key in (inex)th list 
  LinkedList <int> :: iterator i; 
  for (i = table[index].begin(); i != table[index].end(); i++) { 
    if (*i == key) 
      break; 
  } 
  
  // if key is found in hash table, remove it 
  if (i != table[index].end()) 
    table[index].erase(i); 
} 
  
// function to display hash table 
void hash::displayHash() { 
  for (int i = 0; i < BUCKET; i++) { 
    cout << i; 
    for (auto x : table[i]) 
      cout << " --> " << x; 
    cout << endl; 
  } 
}