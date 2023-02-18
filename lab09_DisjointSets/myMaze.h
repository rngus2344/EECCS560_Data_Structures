#ifndef MYMAZE_H
#define MYMAZE_H

#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <iostream>
// #include "myDisjointSets.h"

class myMaze
{
public:
  enum EntryType { WALL, BROKEN, BOUNDARY };

private:
  int size;
  int rowSize;
  int colSize;

  std::vector<int> maze;

public:
  myMaze( const int m, const int n )
  {
    size = m*n;
  }

  ~myMaze( void )
  {
    // maze.clear( );
  }

  void buildMaze( std::vector<std::pair<int, int> > & broken_walls)
  {
    for( int i=0; i<size; i++ )
    {
      broken_walls.push_back( std::make_pair( i, i+1 ) );
    }

  }

  void solveMaze( std::vector<int> & path )
  {
    for( int i=0; i<size; i++ )
    {
      path.push_back( i );
    }
  }
};

#endif
