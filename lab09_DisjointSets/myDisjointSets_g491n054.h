#ifndef MYDISJOINTSETS_H
#define MYDISJOINTSETS_H

#include <vector>

class myDisjointSets
{
public:
  myDisjointSets( )
  { }

  myDisjointSets( int numElements )
  {
    for( int i=0; i<numElements; i++)
    {
      s[i] = -1;
      size[i] = 1;
    }
  }

  int find( int x )
  {
    if( s[x] < 0 )
      return x;
    else
      return s[x] = find( s[x] );
  }

  void unionSets( int root1, int root2 )
  {
    if( s[ root2 ] < s[ root1 ] )  // root2 is deeper
    {
      s[ root1 ] = root2;          // Make root2 new root
      size[ root2 ] = size[ root2 ]+size[ root1 ];
    }
    else
    {
      if( s[ root1 ] == s[ root2 ] )
        --s[ root1 ];             // Update height if same
      s[ root2 ] = root1;         // Make root1 new root
      size[ root1 ] = size[ root1 ]+size[ root2 ];
    }
  }

  int getSetSize( int x ) const
  {
    if( s[x] >= 0 )
      return -1;
    else
      return size[x];
  }

private:
  std::vector<int> s;
  std::vector<int> size;
};

#endif
