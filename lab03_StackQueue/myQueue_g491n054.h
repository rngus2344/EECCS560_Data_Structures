#include <algorithm>

template <typename Object>
class myQueue
{
public:
  myQueue( const int& size )
  {
    theSize = 0;
    theCapacity = size;
    objects = new Object[theCapacity];
  }

  myQueue( const myQueue<Object>& rhs )
  {
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    objects = new Object[theCapacity];

    for( int i=0; i<theSize; i++ )
    {
      objects[i] = rhs.objects[i];
    }
  }

  myQueue& operator= ( const myQueue& rhs )
  {
    myQueue<Object> copyQueue = rhs;
    std::swap( copyQueue, *this );
    return *this;
  }

  myQueue( myQueue<Object>&& rhs )
  {
    theSize = rhs.size( );
    theCapacity = rhs.theCapacity;
    objects = rhs.objects;
  }

  myQueue& operator= ( myQueue&& rhs )
  {
    std::swap( rhs.theSize, *this.theSize );
    std::swap( rhs.theCapacity, *this.theCapacity );
    std::swap( rhs.objects, *this.objects );
    return *this;
  }

  ~myQueue( void )
  {
    delete[] objects;
  }

  void reserve( const int & capacity )
  {
    theCapacity = capacity;
    Object *newObj = new Object[theCapacity];

    for( int i=0; i<theSize; i++ )
    {
      newObj[i] = objects[i];
    }

    std::swap( objects, newObj );
    delete[] newObj;
  }

  void enqueue( const Object& rhs )
  {
    if( theSize == theCapacity )
    {
      reserve( 2*theCapacity+1 );
    }
    objects[theSize++] = rhs;
  }

  void dequeue( void )
  {
    Object *newObj = new Object[theCapacity];

    for( int i=0; i<theSize; i++ )
    {
      newObj[i] = objects[i+1];
    }
    std::swap( objects, newObj );
    delete[] newObj;

    --theSize;
  }

  Object & front( void )
  {
    return objects[0];
  }

  int size( void )
  {
    return theSize;
  }

  bool empty( void )
  {
    return theSize == 0;
  }

private:
  int theSize;
  int theCapacity;
  Object *objects;
};
