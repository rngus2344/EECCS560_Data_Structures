#ifndef MYSTACK
#define MYSTACK

#include <algorithm>

template <typename Object>
class myStack
{
public:
  myStack( const int& size )
  {
    theSize = 0;
    theCapacity = size;
    objects = new Object[theCapacity];
  }

  myStack( const myStack<Object>& rhs )
  {
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    objects = new Object[theCapacity];

    for( int i=0; i<theSize; i++ )
    {
      objects[i] = rhs.objects[i];
    }
  }

  myStack& operator= ( const myStack& rhs )
  {
    myStack<Object> copyStack = rhs;
    std::swap( copyStack, *this );
    return *this;
  }

  myStack( myStack<Object>&& rhs )
  {
    theSize = rhs.size( );
    theCapacity = rhs.theCapacity;
    objects = rhs.objects;
  }

  myStack& operator= ( myStack&& rhs )
  {
    std::swap( rhs.theSize, *this.theSize );
    std::swap( rhs.theCapacity, *this.theCapacity );
    std::swap( rhs.objects, *this.objects );
    return *this;
  }

  ~myStack( void )
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

  void push( const Object& rhs )
  {
    if( theSize == theCapacity )
    {
      reserve( 2*theCapacity+1 );
    }
    objects[theSize++] = rhs;
  }

  void pop( void )
  {
    --theSize;
  }

  Object & top( void )
  {
    return objects[theSize-1];
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

#endif
