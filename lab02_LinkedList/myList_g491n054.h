#include <algorithm>

template <typename Object>
class myList
{
  private:
    struct Node
    {
      Object data;
      Node *prev;
      Node *next;

      Node( const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr )
        : data{ d }, prev{ p }, next{ n } { }

      Node( Object && d, Node * p = nullptr, Node * n = nullptr )
        : data{ std::move( d ) }, prev{ p }, next{ n } { }
    };

  public:
    class const_iterator
    {
      public:
        const_iterator( ) : current{ nullptr }
          { }

        const Object & operator* ( ) const
          { return retrieve( ); }

        const_iterator & operator++ ( )
        {
          current = current->next;
          return *this;
        }

        const_iterator operator++ ( int )
        {
          const_iterator old = *this;
          ++( *this );
          return old;
        }

        const_iterator & operator-- ( )
        {
          current = current->prev;
          return *this;
        }

        const_iterator operator-- ( int )
        {
          const_iterator old = *this;
          --( *this );
          return old;
        }

        bool operator== ( const const_iterator & rhs ) const
          { return current == rhs.current; }
        bool operator!= ( const const_iterator & rhs ) const
          { return !( *this == rhs ); }

      protected:
        Node *current;

        Object & retrieve( ) const
          { return current->data; }

        const_iterator( Node *p ) : current{ p }
          { }

        friend class myList<Object>;
    };

    class iterator : public const_iterator
    {
      public:
        iterator( )
          { }

        Object & operator* ( )
          { return const_iterator::retrieve( ); }

        const Object & operator* ( ) const
          { return const_iterator::operator*( ); }

        iterator & operator++ ( )
        {
          this->current = this->current->next;
          return *this;
        }

        iterator operator++ ( int )
        {
          iterator old = *this;
          ++( *this );
          return old;
        }

        iterator & operator-- ( )
        {
          this->current = this->current->prev;
          return *this;
        }

        iterator operator-- ( int )
        {
          iterator old = *this;
          --( *this );
          return old;
        }

      protected:
        iterator( Node *p ) : const_iterator{ p }
          { }

        friend class myList<Object>;
    };

  public:
    myList( )
      { init( ); }

    myList( const myList & rhs )
    {
      init( );
      for( auto & x : rhs )
        push_back( x );
    }

    ~myList( )
    {
      clear( );
      delete head;
      delete tail;
    }

    myList & operator= ( const myList & rhs )
    {
      myList copy = rhs;
      std::swap( *this, copy );
      return *this;
    }

    myList( myList && rhs )
      : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
      rhs.theSize = 0;
      rhs.head = nullptr;
      rhs.tail = nullptr;
    }

    myList & operator= ( myList && rhs )
    {
      std::swap( theSize, rhs.theSize );
      std::swap( head, rhs.head );
      std::swap( tail, rhs.tail );

      return *this;
    }

    iterator begin( )
      { return { head->next }; }
    const_iterator begin( ) const
      { return { head->next }; }
    iterator end( )
      { return { tail }; }
    const_iterator end( ) const
      { return { tail }; }
    int size( ) const
      { return theSize; }
    bool empty( ) const
      { return size( ) == 0; }

    void clear( )
    {
      while( !empty( ) )
        pop_front( );
    }

    Object & front( )
      { return *begin( ); }
    const Object & front( ) const
      { return *begin( ); }
    Object & back( )
      { return *--end( ); }
    const Object & back( ) const
      { return *--end( ); }
    void push_front( const Object & x )
      { insert( begin( ), x ); }
    void push_front( Object && x )
      { insert( begin( ), std::move( x ) ); }
    void push_back( const Object & x )
      { insert( end( ), x ); }
    void push_back( Object && x )
      { insert( end( ), std::move( x ) ); }
    void pop_front( )
      { erase( begin( ) ); }
    void pop_back( )
      { erase( --end( ) ); }

    iterator insert( iterator itr, const Object & x )
    {
      Node *p = itr.current;
      theSize++;
      return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }

    iterator insert( iterator itr, Object && x )
    {
      Node *p = itr.current;
      theSize++;
      return { p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } };
    }

    iterator erase( iterator itr )
    {
      Node *p = itr.current;
      iterator retVal{ p->next };
      p->prev->next = p->next;
      p->next->prev = p->prev;
      delete p;
      theSize--;

      return retVal;
    }

    iterator erase( iterator from, iterator to )
    {
      for( iterator itr = from; itr != to; )
        itr = erase( itr );

      return to;
    }

    void reverseList( void )
    {
      Node *currentNode = head;
      Node *nextNode = NULL;

      while( currentNode != NULL )
      {
        nextNode = currentNode->next;
        currentNode->next = currentNode->prev;
        currentNode->prev = nextNode;
        currentNode = nextNode;
      }
      currentNode = head;
      head = tail;
      tail = currentNode;
    }

    myList<Object> & appendList( const myList<Object>& linked_list )
    {
      for( auto & x: linked_list )
      {
        push_back( x );
      }
      return *this;
    }

    bool swapAdjElements( iterator &itr )
    {
      Node *currentNode = itr.current;
      Node *prevNode = currentNode->prev;
      ++itr;

      if( itr == end( ) )
      {
        return false;
      }

      Node *adjNode = itr.current;
      currentNode->prev = currentNode->next;
      currentNode->next = adjNode->next;
      adjNode->next->prev = currentNode;
      adjNode->prev = prevNode;
      prevNode->next = adjNode;
      adjNode->next = currentNode;

      return true;
    }

  private:
    int theSize;
    Node *head;
    Node *tail;

    void init( )
    {
      theSize = 0;
      head = new Node;
      tail = new Node;
      head->next = tail;
      tail->prev = head;
    }
};
