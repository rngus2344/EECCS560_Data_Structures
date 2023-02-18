/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file main.cpp
* @date 6/26/2020
* @brief cpp file of main
 ---------------------------------------------------------------------------- */
//Start your program.
#include <iostream>
#include "executive.h"

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    std::cout << "Incorrect number of parameters!\n";
  }
  else
  {
    executive exec(argv[1]); //sample creation of executive object
  }
  return(0);
}

////////////////////////////////////////////////////

#include<bits/stdc++.h> 
using namespace std; 

// Driver program  
int main() 
{ 
  // array that contains keys to be mapped 
  int a[] = {15, 11, 27, 8, 12}; 
  int n = sizeof(a)/sizeof(a[0]); 
  
  // insert the keys into the hash table 
  Hash h(7);   // 7 is count of buckets in 
               // hash table 
  for (int i = 0; i < n; i++)  
    h.insertItem(a[i]);   
  
  // delete 12 from hash table 
  h.deleteItem(12); 
  
  // display the Hash table 
  h.displayHash(); 
  
  return 0; 
}