#ifndef MYHASHTABLE
#define MYHASHTABLE

#include <vector>
#include <algorithm>

template <typename HashedObj>
class myHashTable
{
public:
  enum EntryType { ACTIVE, EMPTY, DELETED };

private:
  struct HashEntry
  {
    HashedObj element;
    EntryType info;

    HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
      : element{ e }, info{i}{ }
    HashEntry( HashedObj && e, EntryType i = EMPTY )
      : element{ std::move( e ) }, info{i}{ }

    bool operator ==( const HashEntry& p ) const
    {
      return ( this->element.getKey( ) == p.element.getKey( ) );
    }
  };

public:
  explicit myHashTable( int size = 101 ) : m_hashTable( nextPrime( size ) )
  {
    makeEmpty( );
  }

  void makeEmpty( )
  {
    currentSize = 0;
    for( auto & entry : m_hashTable )
    {
      entry.info = EMPTY;
    }
  }

  size_t strToHashValue ( const std::string & str )
  {
    size_t hashVal = 0;
    // From textbook page 198
    for( char ch : str )
    {
      hashVal = 3 * hashVal + ch;
    }
    return hashVal;
  }

  // From textbook page 233
  const int DIGS = 31;
  const int mersennep = ( 1<<DIGS ) - 1;

  int universalHash( int x, int A, int B, int M )
  {
    long long hashVal = static_cast<long long>( A ) * x + B;

    hashVal = ( ( hashVal >> DIGS ) + ( hashVal & mersennep ) );
    if( hashVal >= mersennep )
      hashVal -= mersennep;

    return static_cast<int>( hashVal ) % M;
  }

  bool contains( const HashedObj & x )
  {
    return isActive( findPosition( x ) );
  }

  size_t myhash( const HashedObj & x ) const
  {
    static myHashTable<HashEntry> hf;
    return hf.strToHashValue( x.getKey( ) ) % m_hashTable.size( );
  }

  int findPosition( const HashedObj & x ) const
  {
    int offset = 1;
    int currentPos = myhash( x );

    while( m_hashTable[currentPos].info != EMPTY && !( m_hashTable[currentPos].element == x ) )
    {
      currentPos += offset;
      offset += 2;
      if( currentPos >= m_hashTable.size( ) )
      {
        currentPos -= m_hashTable.size( );
      }
    }
    return currentPos;
  }

  bool isActive( int currentPos ) const
  {
    return m_hashTable[currentPos].info == ACTIVE;
  }

  bool isPrime( int n )
  {
    if (n == 0 || n == 1)
    {
      return false;
    }
    else
    {
      for( int i = 2; i <= n / 2; ++i )
      {
        if( n % i == 0 )
        {
          return false;
          break;
        }
      }
      return true;
    }
  }

  int nextPrime( int n )
  {
    int prime = n;
    bool found = false;

    if ( n <= 1 )
    {
      return 2;
    }
    while ( !found )
    {
      prime++;
      if ( isPrime( prime ) )
      {
        found = true;
      }
    }
    return prime;
  }

  void rehash( )
  {
    std::vector<HashEntry> oldHashTable = m_hashTable;

    m_hashTable.resize( nextPrime( 2 * oldHashTable.size( ) ) );
    for( auto & entry : m_hashTable )
    {
      entry.info = EMPTY;
    }

    currentSize = 0;
    for( auto & entry : oldHashTable )
    {
      if( entry.info == ACTIVE )
      {
        insert( std::move( entry.element ) );
      }
    }
  }

  bool insert( const HashedObj & x )
  {
    int currentPos = findPosition( x );
    if( isActive( currentPos ) )
    {
      return false;
    }

    m_hashTable[currentPos].element = x;
    m_hashTable[currentPos].info = ACTIVE;

    if( ++currentSize > m_hashTable.size( ) / 2 )
    {
      rehash( );
    }
    return true;
  }

  bool insert( HashedObj && x )
  {
    int currentPos = findPosition( x );
    if( isActive( currentPos ) )
    {
      return false;
    }

    m_hashTable[currentPos].element = x;
    m_hashTable[currentPos].info = ACTIVE;

    if( ++currentSize > m_hashTable.size( ) / 2 )
    {
      rehash( );
    }
    return true;
  }

  bool remove( const HashedObj & x )
  {
    int currentPos = findPosition( x );
    if( !isActive( currentPos ) )
    {
      return false;
    }

    m_hashTable[currentPos].info = DELETED;
    return true;
  }

private:
  std::vector<HashEntry> m_hashTable;
  int currentSize;
};

#endif
