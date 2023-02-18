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
  struct myMazeCell
  {
    int height;
    EntryType rightWall;
    EntryType leftWall;
    EntryType upWall;
    EntryType downWall;
    std::vector<int> connected;
    bool passed;
  };

  int size;
  int rowSize;
  int colSize;

  std::vector<myMazeCell> maze;

public:
  myMaze( const int m, const int n )
  {
    size = m*n;
    rowSize = m;
    colSize = n;
    maze.resize( m*n );

    for( int i=0; i<m*n; i++ )
    {
      maze[i].connected.push_back( i );
      maze[i].passed = false;
      maze[i].height = -1;

      if( i == 0 )
      {
        maze[i].leftWall = BOUNDARY;
        maze[i].upWall = BOUNDARY;
        maze[i].rightWall = WALL;
        maze[i].downWall = WALL;
      }
      else if( i == size-1 )
      {
        maze[i].rightWall = BOUNDARY;
        maze[i].downWall = BOUNDARY;
        maze[i].leftWall = WALL;
        maze[i].upWall = WALL;
      }
      else
      {
        if( i%n == n-1 )
        {
          maze[i].rightWall = BOUNDARY;
          maze[i].leftWall = WALL;
        }
        else if( i%n == 0 )
        {
          maze[i].leftWall = BOUNDARY;
          maze[i].rightWall = WALL;
        }
        else
        {
          maze[i].rightWall = WALL;
          maze[i].leftWall = WALL;
        }
        if( i >= (m-1)*n )
        {
          maze[i].downWall = BOUNDARY;
          maze[i].upWall = WALL;
        }
        else if( i < n )
        {
          maze[i].upWall = BOUNDARY;
          maze[i].downWall = WALL;
        }
        else
        {
          maze[i].upWall = WALL;
          maze[i].downWall = WALL;
        }
      }
    }
  }

  ~myMaze( void )
  {
    maze.clear( );
  }

  int ranNum( int limit )
  {
    int r = rand( ) % limit;
		return r;
	}

  bool isConnected( int a, int b )
  {
    if( std::find( maze[a].connected.begin( ), maze[a].connected.end( ), b ) != maze[a].connected.end( ) )
      return true;
    return false;
  }

  void buildMaze( std::vector<std::pair<int, int> > & broken_walls)
  {
    do
    {
      int r = ranNum( size );
      int x = ranNum( 2 );

      if( x == 0 )
      {
        if( maze[r].rightWall == WALL && !isConnected( r, r+1 ) )
        {
          // if( maze[r].height < maze[r+1] )
          // {
          //   maze[r].height = maze[r+1];
          // }
          // else
          // {
          //   if( maze[r].height == maze[r+1] )
          //     --maze[r].height;
          //   maze[r+1].height = r;
          // }
          broken_walls.push_back( std::make_pair( r, r+1 ) );
          maze[r].rightWall = BROKEN;
          maze[r+1].leftWall = BROKEN;
          maze[r].connected.insert( maze[r].connected.end( ), maze[r+1].connected.begin( ), maze[r+1].connected.end( ) );
          maze[r+1].connected = maze[r].connected;
          for( int i=0; i<maze[r].connected.size( ); i++ )
          {
            maze[maze[r].connected[i]].connected = maze[r].connected;
          }
        }
      }
      else
      {
        if( maze[r].downWall == WALL && !isConnected( r, r+colSize ) )
        {
          broken_walls.push_back( std::make_pair( r, r+colSize ) );
          maze[r].downWall = BROKEN;
          maze[r+colSize].upWall = BROKEN;
          maze[r].connected.insert( maze[r].connected.end( ), maze[r+colSize].connected.begin( ), maze[r+colSize].connected.end( ) );
          maze[r+colSize].connected = maze[r].connected;
          for( int i=0; i<maze[r].connected.size( ); i++ )
          {
            maze[maze[r].connected[i]].connected = maze[r].connected;
          }
        }
      }
    } while ( broken_walls.size( ) < size-1 );
    // for( int i=0; i<size-1; i++ )
    // {
    //   std::cout << broken_walls[i].first << ", " << broken_walls[i].second << '\n';
    // }
  }

  void solveMaze( std::vector<int> & path )
  {
    // for( int i=0; i<size; i++ )
    // {
    //   for( int j=0; j<maze[i].connected.size( ); j++ )
    //     std::cout << maze[i].connected[j] << ' ';
    //   std::cout << '\n';
    // }

    int count = 0;
    maze[0].passed = true;
    path.push_back( 0 );
    std::vector<int> passedWall;
    // path.resize( size-1 );

    do
    {
      if( maze[count].rightWall == BROKEN && maze[count+1].passed == false )
      {
        path.push_back( count+1 );
        maze[count+1].passed = true;
        count++;
        passedWall.push_back( 1 );
      }
      else if( maze[count].downWall == BROKEN && maze[count+colSize].passed == false )
      {
        path.push_back( count+colSize );
        maze[count+colSize].passed = true;
        count = count + colSize;
        passedWall.push_back( 2 );
      }
      else if( maze[count].leftWall == BROKEN && maze[count-1].passed == false )
      {
        path.push_back( count-1 );
        maze[count-1].passed = true;
        count--;
        passedWall.push_back( 3 );
      }
      else if( maze[count].upWall == BROKEN && maze[count-colSize].passed == false )
      {
        path.push_back( count-colSize );
        maze[count-colSize].passed = true;
        count = count - colSize;
        passedWall.push_back( 4 );
      }
      else
      {
        if( passedWall.back( ) == 1 )
        {
          path.pop_back( );
          count--;
          passedWall.pop_back( );
        }
        else if( passedWall.back( ) == 2 )
        {
          path.pop_back( );
          count = count - colSize;
          passedWall.pop_back( );
        }
        else if( passedWall.back( ) == 3 )
        {
          path.pop_back( );
          count++;
          passedWall.pop_back( );
        }
        else if( passedWall.back( ) == 4 )
        {
          path.pop_back( );
          count = count + colSize;
          passedWall.pop_back( );
        }
      }
    } while ( path.back( ) < size-1 );
    // for( int i=0; i<path.size( ); i++ )
    // {
    //   std::cout << path[i] << '\n';
    // }
  }
};

#endif
