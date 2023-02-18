#ifndef MYBST
#define MYBST

#include <iostream>

template <typename Comparable>
class myBST
{
public:
  myBST( )
  {
    root = nullptr;
  }

  myBST( const myBST & rhs ) : root{ nullptr }
  {
    root = clone( rhs.root );
  }

  myBST( myBST && rhs )
  {
    root = clone( rhs.root );
  }

  ~myBST( )
  {
    makeEmpty( );
  }

  const Comparable & findMin( ) const
  {
    findMin( root );
  }

  const Comparable & findMax( ) const
  {
    findMax( root );
  }

  bool contains( const Comparable & x ) const
  {
    return contains( x, root );
  }

  bool isEmpty( ) const
  {
    if( root == nullptr )
      return true;
    else
      return false;
  }

  void makeEmpty( )
  {
    makeEmpty( root );
  }

  void insert( const Comparable & x )
  {
    insert( x, root );
  }

  void insert( Comparable && x )
  {
    insert( x, root );
  }

  void remove( const Comparable & x )
  {
    remove( x, root );
  }

  // myBST & operator=( const myBST & rhs )
  // {
  //
  // }
  //
  // myBST & operator=( myBST && rhs )
  // {
  //
  // }

  void printPreOrder( void )
  {
    std::cout << root->element << ' ';
    if( root->left != nullptr )
    {
      preOrder( root->left );
    }
    if( root->right != nullptr )
    {
      preOrder( root->right );
    }
    std::cout << '\n';
  }

  void printPostOrder( void )
  {
    if( root->left != nullptr )
    {
      postOrder( root->left );
    }
    if( root->right != nullptr )
    {
      postOrder( root->right );
    }
    std::cout << root->element << " \n";
  }

private:
  struct BinaryNode
  {
    Comparable element;
    BinaryNode*left;
    BinaryNode*right;

    BinaryNode( const Comparable & theElement, BinaryNode*lt, BinaryNode*rt )
      : element{ theElement }, left{ lt }, right{ rt } { }

    BinaryNode( Comparable && theElement, BinaryNode*lt, BinaryNode*rt )
      : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
  };

  BinaryNode*root;

  void insert( const Comparable & x, BinaryNode*&t)
  {
    if( t == nullptr )
      t = new BinaryNode{ x, nullptr, nullptr };
    else if( x < t->element )
      insert( x, t->left );
    else if( t->element < x )
      insert( x, t->right );
    else
      ;  // Duplicate; do nothing
  }

  void insert( Comparable && x, BinaryNode*&t)
  {
    if( t == nullptr )
      t = new BinaryNode{ std::move( x ), nullptr, nullptr };
    else if( x < t->element )
      insert( std::move( x ), t->left );
    else if( t->element < x )
      insert( std::move( x ), t->right );
    else
      ;  // Duplicate; do nothing
  }

  void remove( const Comparable & x, BinaryNode*&t)
  {
    if( t == nullptr )
      return;   // Item not found; do nothing
    if( x < t->element )
      remove( x, t->left );
    else if( t->element < x )
      remove( x, t->right );
    else if( t->left != nullptr && t->right != nullptr ) // Two children
    {
      t->element = findMin( t->right )->element;
      remove( t->element, t->right );
    }
    else
    {
      BinaryNode *oldNode = t;
      t = ( t->left != nullptr ) ? t->left : t->right;
      delete oldNode;
    }
  }

  BinaryNode*findMin( BinaryNode*t ) const
  {
    if( t == nullptr )
      return nullptr;
    if( t->left == nullptr )
      return t;
    return findMin( t->left );
  }

  BinaryNode*findMax( BinaryNode*t ) const
  {
    if( t != nullptr )
      while( t->right != nullptr )
        t = t->right;
    return t;
  }

  bool contains( const Comparable & x, BinaryNode*t ) const
  {
    if( t == nullptr )
      return false;
    else if( x < t->element )
      return contains( x, t->left );
    else if( t->element < x )
      return contains( x, t->right );
    else
      return true;    // Match
  }

  void makeEmpty( BinaryNode*&t )
  {
    if( t != nullptr )
    {
      makeEmpty( t->left );
      makeEmpty( t->right );
      delete t;
    }
    t = nullptr;
  }

  BinaryNode*clone( BinaryNode*t ) const
  {
    if( t == nullptr )
      return nullptr;
    else
      return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
  }

  void preOrder( BinaryNode*t )
  {
    std::cout << t->element << ' ';
    if( t->left != nullptr )
    {
      preOrder( t->left );
    }
    if( t->right != nullptr )
    {
      preOrder( t->right );
    }
  }

  void postOrder( BinaryNode*t )
  {
    if( t->left != nullptr )
    {
      postOrder( t->left );
    }
    if( t->right != nullptr )
    {
      postOrder( t->right );
    }
    std::cout << t->element << ' ';
  }
};

#endif
