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

  NodeType( std::string name )
  {
    city = name;
  }
};

class EdgeType
{
public:
  int distance;
  bool valid; // or visited

  EdgeType( int d )
  {
    distance = d;
  }
};

class myGraph
{
private:
  // std::vector<std::list<std::pair<NodeType, EdgeType> > > graph;
  std::vector<NodeType> graph_node;
  // std::vector<std::list<EdgeType> > graph_edge;
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
    int id = graph_size;
    graph_node.push_back( n );
    graph_node.back( ).city_id = id;
    graph_size++;
    graph_edge.resize( graph_size );
    return id;
  }

  NodeType getNode( const int id )
  {
    return graph_node[id-1];
  }

  bool addEdge( const EdgeType & e, const int id1, const int id2 )
  {
    if( id1 >= graph_size || id2 >= graph_size || id1 < 1 || id2 < 1 )
    {
      return false;
    }
    else
    {
      std::pair<int, EdgeType> e1( id2-1, e );
      std::pair<int, EdgeType> e2( id1-1, e );

      graph_edge[id1-1].push_back( e1 );
      graph_edge[id2-1].push_back( e2 );

      return true;
    }
  }

  bool isConnected( const int id1, const int id2 )
  {
    int count = 0;

    if( id1 >= graph_size || id2 >= graph_size || id1 < 1 || id2 < 1 )
    {
      return false;
    }
    else
    {
      auto it1 = graph_edge[id1-1].begin( );

      for( int i=0; i<graph_edge[id1-1].size( ); i++ )
      {
        if( ( *it1 ).first == id2-1 )
        {
          count++;
        }
        std::advance( it1, 1 );
      }

      auto it2 = graph_edge[id2-1].begin( );

      for( int i=0; i<graph_edge[id2-1].size( ); i++ )
      {
        if( ( *it2 ).first == id1-1 )
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
    auto it = graph_edge[id1-1].begin( );

    for( int i=0; i<graph_edge[id1-1].size( ); i++ )
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
    if( id >= graph_size || id < 1 )
      return 0;
    else
      return graph_edge[id-1].size( );
  }

  bool deleteNode( const int id )
  {
    if( id >= graph_size || id < 1 )
    {
      return false;
    }
    else
    {
      for( int i=0; i<graph_edge.size( ); i++ )
      {
        auto it = graph_edge[i].begin( );

        if( ( *it ).first == id-1 )
        {
          it = graph_edge[i].erase( it );
        }
        std::advance( it, 1 );
      }

      graph_node.erase( graph_node.begin( )+id-1 );
      graph_edge[id-1].erase( graph_edge[id-1].begin( ), graph_edge[id-1].end( ) );
      graph_size--;
      return true;
    }
  }

  bool deleteEdge( const int id1, const int id2 )
  {
    auto it1 = graph_edge[id1-1].begin( );
    auto it2 = graph_edge[id2-1].begin( );
    int count = 0;

    if( id1 >= graph_size || id2 >= graph_size || id1 < 1 || id2 < 1 )
    {
      return false;
    }
    else
    {
      for( int i=0; i<graph_edge[id1-1].size( ); i++ )
      {
        if( ( *it1 ).first == id2-1 )
        {
          it1 = graph_edge[id1-1].erase( it1 );
          count++;
        }
        std::advance( it1, 1 );
      }

      for( int i=0; i<graph_edge[id2-1].size( ); i++ )
      {
        if( ( *it2 ).first == id1-1 )
        {
          it2 = graph_edge[id2-1].erase( it2 );
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
};

#endif
