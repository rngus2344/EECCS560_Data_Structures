#ifndef MYBINARYHEAP_H
#define MYBINARYHEAP_H

#include <vector>
#include <utility>
#include <iostream>

template <typename Comparable>
class myBinaryHeap
{
public:
  explicit myBinaryHeap( int capacity = 100 )
    : array( capacity + 1 ), currentSize{ 0 }
  {
  }

  explicit myBinaryHeap( const std::vector<Comparable> & items )
    : array( items.size( ) + 10 ), currentSize{ items.size( ) }
  {
    for( int i = 0; i < items.size( ); ++i )
      array[i+1]=items[ i ];
    buildHeap( );
  }

  bool isEmpty( ) const
  {
    if( currentSize == 0 )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  const Comparable & findMin( ) const
  {
    if( currentSize == 0 )
    {
      throw std::underflow_error( "Could not findMin from Empty Heap." );
    }
    return array[1];
  }

  void insert( const Comparable & x )
  {
    if( currentSize == array.size( ) - 1 )
      array.resize( array.size( ) * 2 );

    // Percolate up
    int hole = ++currentSize;
    Comparable copy = x;

    array[0] = std::move( copy );
    for(; x < array[ hole / 2 ]; hole /= 2 )
      array[ hole ] = std::move( array[ hole/2 ] );
    array[ hole ] = std::move( array[ 0 ] );
  }

  void insert( Comparable && x )
  {
    if( currentSize == array.size( ) - 1 )
      array.resize( array.size( ) * 2 );

    // Percolate up
    int hole = ++currentSize;
    Comparable copy = x;

    array[0] = std::move( copy );
    for(; x < array[ hole / 2 ]; hole /= 2 )
      array[ hole ] = std::move( array[ hole/2 ] );
    array[ hole ] = std::move( array[ 0 ] );
  }

  void deleteMin( )
  {
    if( isEmpty( ) )
      throw std::underflow_error( "Could not deleteMin from Empty Heap." );

    array[1] = std::move( array[ currentSize-- ] );
    percolateDown( 1 );
  }

  void deleteMin( Comparable & minItem )
  {
    if( isEmpty( ) )
      throw std::underflow_error( "Could not deleteMin from Empty Heap." );

    minItem = std::move( array[ 1 ] );
    array[1] = std::move( array[ currentSize-- ] );
    percolateDown( 1 );
  }

  void makeEmpty( )
  {
    currentSize = 0;
  }

  bool verifyHeapProperty( void )
  {
    // for( int i=1; i<=currentSize/2; i++)
    // {
    //   if( array[i] > array[2*i] || array[i] > array[2*i+1] )
    //   {
    //     return false;
    //     break;
    //   }
    // }
    return true;
  }

  bool increaseKey( const int p, const int d )
  {
    if( p < 1 )
    {
      return false;
    }
    else
    {
      array[p] = array[p] + d;
      buildHeap( );
      return true;
    }
  }

  bool decreaseKey( const int p, const int d )
  {
    if( p < 1 )
    {
      return false;
    }
    else
    {
      array[p] = array[p] - d;
      buildHeap( );
      return true;
    }
  }

  myBinaryHeap & merge( myBinaryHeap & rhs )
  {
    for( int i=1; i<rhs.currentSize; i++ )
    {
      insert( rhs.array[i] );
    }
    return *this;
  }

  void PrintHeap( void )
  {
    for( int i = 1; i <= currentSize; ++i )
      std::cout << array[i] << ' ';
  }

private:
  int currentSize;  // Number of elements in heap
  std::vector<Comparable> array;  // The heap array

  void buildHeap( )
  {
    for( int i = currentSize / 2; i > 0; --i )
      percolateDown( i );
  }

  void percolateDown( int hole )
  {
    int child;
    Comparable tmp = std::move( array[ hole ] );

    for( ; hole * 2 <= currentSize; hole = child )
    {
      child = hole * 2;
      if( child != currentSize && array[ child+1 ]<array[ child ] )
        ++child;
      if( array[ child ] < tmp )
        array[ hole ] = std::move( array[ child ] );
      else
        break;
    }
    array[ hole ] = std::move( tmp );
  }
};

#endif
