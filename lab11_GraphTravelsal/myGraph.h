#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <iterator>
#include <utility>
#include <algorithm>
#include <cstdlib>

class NodeType
{
public:
  std::string city;
  int city_id;
  bool visited = false;
  bool checked = false;

  NodeType( std::string name )
  {
    city = name;
  }
};

class EdgeType
{
public:
  int distance;
  // bool traveled = false; // or valid

  EdgeType( int d )
  {
    distance = d;
  }
};

class myGraph
{
private:
  std::vector<NodeType> graph_node;
  std::vector<std::list<std::pair<int, EdgeType> > > graph_edge;
  int graph_size;

public:
  myGraph( )
  {
    graph_size = 0;
  }

  myGraph( const myGraph& rhs ) // copy constructor
  {
    graph_size = rhs.graph_size;
    for( int i=0; i<graph_size; i++ )
    {
      graph_node[i] = rhs.graph_node[i];
      graph_edge[i] = rhs.graph_edge[i];
    }
  }

  myGraph& operator= ( const myGraph& rhs ) // copy assignment
  {
    graph_size = rhs.graph_size;
    for( int i=0; i<graph_size; i++ )
    {
      graph_node[i] = rhs.graph_node[i];
      graph_edge[i] = rhs.graph_edge[i];
    }
    return *this;
  }

  myGraph( myGraph&& rhs ) // move constructor
  {
    graph_size = rhs.graph_size;
    graph_node = rhs.graph_node;
    graph_edge = rhs.graph_edge;
  }

  myGraph& operator= ( myGraph&& rhs ) // copy assignment
  {
    graph_size = rhs.graph_size;
    for( int i=0; i<graph_size; i++ )
    {
      graph_node[i] = rhs.graph_node[i];
      graph_edge[i] = rhs.graph_edge[i];
    }
    return *this;
  }

  ~myGraph( ) // destructor
  {
    graph_node.clear( );
    graph_edge.clear( );
  }

  int addNode( const NodeType & n )
  {
    int id = graph_size+1;
    graph_node.push_back( n );
    graph_node.back( ).city_id = id;
    graph_size++;
    graph_edge.resize( graph_size );
    return id;
  }

  NodeType getNode( const int id )
  {
    return graph_node[id];
  }

  bool addEdge( const EdgeType & e, const int id1, const int id2 )
  {
    if( id1 > graph_size || id2 > graph_size || id1 < 1 || id2 < 1 )
    {
      return false;
    }
    else
    {
      std::pair<int, EdgeType> e1( id2, e );
      std::pair<int, EdgeType> e2( id1, e );

      graph_edge[id1-1].push_back( e1 );
      graph_edge[id2-1].push_back( e2 );

      return true;
    }
  }

  bool isConnected( const int id1, const int id2 )
  {
    int count = 0;

    if( id1 > graph_size || id2 > graph_size || id1 < 1 || id2 < 1 )
    {
      return false;
    }
    else
    {
      auto it1 = graph_edge[id1-1].begin( );

      for( int i=0; i<graph_edge[id1-1].size( ); i++ )
      {
        if( ( *it1 ).first == id2 )
        {
          count++;
        }
        std::advance( it1, 1 );
      }

      auto it2 = graph_edge[id2-1].begin( );

      for( int i=0; i<graph_edge[id2-1].size( ); i++ )
      {
        if( ( *it2 ).first == id1 )
        {
          count++;
        }
        std::advance( it2, 1 );
      }

      if( count > 0 )
        return true;
      else
        return false;
    }
  }

  EdgeType getEdge( const int id1, const int id2 )
  {
    auto it = graph_edge[id1].begin( );

    for( int i=0; i<graph_edge[id1].size( ); i++ )
    {
      if( ( *it ).first == id2 )
      {
        return ( *it ).second;
        break;
      }
      std::advance( it, 1 );
    }
    return 0;
  }

  int getDegree( const int id )
  {
    if( id > graph_size || id < 0 )
      return 0;
    else
      return graph_edge[id].size( );
  }

  bool deleteNode( const int id )
  {
    if( id > graph_size || id < 0 )
    {
      return false;
    }
    else
    {
      for( int i=0; i<graph_edge.size( ); i++ )
      {
        auto it = graph_edge[i].begin( );

        if( ( *it ).first == id )
        {
          it = graph_edge[i].erase( it );
        }
        std::advance( it, 1 );
      }

      graph_node.erase( graph_node.begin( )+id );
      graph_edge[id].erase( graph_edge[id].begin( ), graph_edge[id].end( ) );
      graph_size--;
      return true;
    }
  }

  bool deleteEdge( const int id1, const int id2 )
  {
    auto it1 = graph_edge[id1].begin( );
    auto it2 = graph_edge[id2].begin( );
    int count = 0;

    if( id1 > graph_size || id2 > graph_size || id1 < 0 || id2 < 0 )
    {
      return false;
    }
    else
    {
      for( int i=0; i<graph_edge[id1].size( ); i++ )
      {
        if( ( *it1 ).first == id2 )
        {
          it1 = graph_edge[id1].erase( it1 );
          count++;
        }
        std::advance( it1, 1 );
      }

      for( int i=0; i<graph_edge[id2].size( ); i++ )
      {
        if( ( *it2 ).first == id1 )
        {
          it2 = graph_edge[id2].erase( it2 );
          count++;
        }
        std::advance( it2, 1 );
      }

      if( count > 0 )
        return true;
      else
        return false;
    }
  }

  void BFS( const int id, std::vector<std::string> & path )
  {
    auto it = graph_edge[id-1].begin( );
    std::list<int> tempID;

    if( graph_node[id-1].visited == false )
    {
      path.push_back( graph_node[id-1].city );
      graph_node[id-1].visited = true;
    }

    for( int i=0; i<graph_edge[id-1].size( ); i++ )
    {
      tempID.push_back( ( *it ).first );
      std::advance( it, 1 );
    }

    tempID.sort( );
    auto tempIt = tempID.begin( );

    for( int i=0; i<tempID.size( ); i++ )
    {
      if( graph_node[tempID.back( )-1].visited == false )
      {
        path.push_back( graph_node[( *tempIt )-1].city );
        graph_node[( *tempIt )-1].visited = true;
      }
      std::advance( tempIt, 1 );
    }

    graph_node[id-1].checked = true;

    while( !tempID.empty( ) )
    {
      BFSRecursive( tempID.front( ), path, tempID );
      tempID.pop_front( );
    }

    for( int j=0; j<graph_node.size( ); j++ )
    {
      graph_node[j].visited = false;
      graph_node[j].checked = false;
    }
  }

  void BFSRecursive( const int id, std::vector<std::string> & path, std::list<int> & tempID )
  {
    if( graph_node[id-1].checked == false )
    {
      auto it = graph_edge[id-1].begin( );
      std::list<int> tempID2;

      if( graph_node[id-1].visited == false )
      {
        path.push_back( graph_node[id-1].city );
        graph_node[id-1].visited = true;
      }

      for( int i=0; i<graph_edge[id-1].size( ); i++ )
      {
        tempID2.push_back( ( *it ).first );
        std::advance( it, 1 );
      }

      tempID2.sort( );
      auto tempIt2 = tempID2.begin( );
      auto tempIt = tempID.end( );
      for( int i=0; i<tempID2.size( ); i++ )
      {
        tempID.push_back( graph_node[( *tempIt2 )-1].city_id );
        std::advance( tempIt2, 1 );
      }
      tempIt2 = tempID2.begin( );
      std::advance( tempIt, 1 );

      for( int i=0; i<tempID.size( ); i++ )
      {
        if( graph_node[( *tempIt )-1].visited == false )
        {
          path.push_back( graph_node[( *tempIt )-1].city );
          graph_node[( *tempIt )-1].visited = true;
        }
        std::advance( tempIt, 1 );
      }

      graph_node[id-1].checked = true;
    }
    else
      return;
  }

  void DFS( const int id, std::vector<std::string> & path )
  {
    auto it = graph_edge[id-1].begin( );
    std::list<int> tempID;

    if( graph_node[id-1].visited == false )
    {
      path.push_back( graph_node[id-1].city );
      graph_node[id-1].visited = true;
    }

    for( int i=0; i<graph_edge[id-1].size( ); i++ )
    {
      tempID.push_back( ( *it ).first );
      std::advance( it, 1 );
    }

    tempID.sort( );
    auto tempIt = tempID.begin( );

    for( int i=0; i<tempID.size( ); i++ )
    {
      if( graph_node[( *tempIt )-1].visited == false )
      {
        path.push_back( graph_node[( *tempIt )-1].city );
        graph_node[( *tempIt )-1].visited = true;
        DFSRecursive( ( *tempIt ), path, tempID );
        tempID.pop_back( );
      }
      std::advance( tempIt, 1 );
    }

    graph_node[id-1].checked = true;

    while( !tempID.empty( ) )
    {
      DFSRecursive( tempID.back( ), path, tempID );
      tempID.pop_back( );
    }

    for( int j=0; j<graph_node.size( ); j++ )
    {
      graph_node[j].visited = false;
      graph_node[j].checked = false;
    }
  }

  void DFSRecursive( const int id, std::vector<std::string> & path, std::list<int> & tempID )
  {
    if( graph_node[id-1].checked == false )
    {
      auto it = graph_edge[id-1].begin( );
      std::list<int> tempID2;

      if( graph_node[id-1].visited == false )
      {
        path.push_back( graph_node[id-1].city );
        graph_node[id-1].visited = true;
      }

      for( int i=0; i<graph_edge[id-1].size( ); i++ )
      {
        tempID2.push_back( ( *it ).first );
        std::advance( it, 1 );
      }

      tempID2.sort( );
      auto tempIt2 = tempID2.begin( );
      for( int i=0; i<tempID2.size( ); i++ )
      {
        tempID.push_back( tempID2.front( ) );
        std::advance( tempIt2, 1 );
      }
      tempIt2 = tempID2.begin( );

      for( int i=0; i<tempID2.size( ); i++ )
      {
        if( graph_node[( *tempIt2 )-1].visited == false )
        {
          path.push_back( graph_node[( *tempIt2 )-1].city );
          graph_node[( *tempIt2 )-1].visited = true;
          DFSRecursive( ( *tempIt2 ), path, tempID );
        }
        std::advance( tempIt2, 1 );
      }

      graph_node[id-1].checked = true;
    }
    else
      return;
  }

  int shortestPath( const int id1, const int id2, std::vector<std::string> & path )
  {
    auto it = graph_edge[id1-1].begin( );
    std::list<int> tempID;
    std::vector<int> shortest;
    std::vector<std::list<std::string> > tempPath;

    for( int i=0; i<graph_size; i++ )
    {
      shortest.push_back( 0 );
    }

    tempPath.resize( graph_size );
    tempPath[id1-1].push_back( graph_node[id1-1].city );

    for( int i=0; i<graph_edge[id1-1].size( ); i++ )
    {
      tempID.push_back( ( *it ).first );
      shortest[tempID.back( )-1] = ( *it ).second.distance;
      // ( *it ).second.traveled = true;
      tempPath[tempID.back( )-1].push_back( graph_node[id1-1].city );
      tempPath[tempID.back( )-1].push_back( graph_node[tempID.back( )-1].city );
      std::advance( it, 1 );
    }
    graph_node[id1-1].checked = true;

    while( !tempID.empty( ) )
    {
      SPRecursive( tempID.front( ), tempID, shortest, tempPath );
      tempID.pop_front( );
    }

    for( int j=0; j<graph_node.size( ); j++ )
    {
      graph_node[j].visited = false;
      graph_node[j].checked = false;
    }

    auto tempIt = tempPath[id2-1].begin( );

    for( int i=0; i<tempPath[id2-1].size( ); i++ )
    {
      path.push_back( ( *tempIt ) );
      std::advance( tempIt, 1 );
    }
    return shortest[id2-1];
  }

  void SPRecursive( const int id1, std::list<int> & tempID, std::vector<int> & shortest, std::vector<std::list<std::string> > & tempPath )
  {
    if( graph_node[id1-1].checked == false )
    {
      auto it = graph_edge[id1-1].begin( );

      for( int i=0; i<graph_edge[id1-1].size( ); i++ )
      {
        if( graph_node[( *it ).first-1].checked == false )
        {
          if( std::find( tempID.begin( ), tempID.end( ), ( *it ).first ) == tempID.end( ) )
          {
            tempID.push_back( ( *it ).first );
            if( shortest[tempID.back( )-1] == 0 )
            {
              shortest[tempID.back( )-1] = shortest[id1-1] + ( *it ).second.distance;
              // ( *it ).second.traveled = true;
              tempPath[tempID.back( )-1] = tempPath[id1-1];
              tempPath[tempID.back( )-1].push_back( graph_node[tempID.back( )-1].city );
            }
            else if( shortest[( *it ).first-1] > shortest[id1-1] + ( *it ).second.distance )
            {
              shortest[( *it ).first-1] = shortest[id1-1] + ( *it ).second.distance;
              // ( *it ).second.traveled = true;
              tempPath[( *it ).first-1].clear( );
              tempPath[( *it ).first-1] = tempPath[id1-1];
              tempPath[( *it ).first-1].push_back( graph_node[( *it ).first-1].city );
            }
          }
          else
          {
            if( shortest[( *it ).first-1] > shortest[id1-1] + ( *it ).second.distance )
            {
              shortest[( *it ).first-1] = shortest[id1-1] + ( *it ).second.distance;
              // ( *it ).second.traveled = true;
              tempPath[( *it ).first-1].clear( );
              tempPath[( *it ).first-1] = tempPath[id1-1];
              tempPath[( *it ).first-1].push_back( graph_node[( *it ).first-1].city );
            }
          }
        }
        std::advance( it, 1 );
      }
      graph_node[id1-1].checked = true;
    }
    else
      return;
  }
};

#endif
