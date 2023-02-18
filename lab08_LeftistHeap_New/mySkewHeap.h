#ifndef MYSKEWHEAP_H
#define MYSKEWHEAP_H

#include <iostream>

template <typename Comparable>
class mySkewHeap
{
public:
  mySkewHeap( )
  {
    root = nullptr;
  }

  // mySkewHeap( const mySkewHeap & rhs )
  // {
  //
  // }
  //
  // mySkewHeap( mySkewHeap && rhs )
  // {
  //
  // }

  ~mySkewHeap( )
  {
    makeEmpty( );
  }


  // mySkewHeap & operator=( const mySkewHeap & rhs )
  // {
  //
  // }
  //
  // mySkewHeap & operator=( mySkewHeap && rhs )
  // {
  //
  // }


  bool isEmpty( ) const
  {
    if( root == nullptr )
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
    return root->element;
  }


  void insert( const Comparable & x )
  {
    root = merge( new mySkewNode{ x }, root );
  }

  void insert( Comparable && x )
  {
    root = merge( new mySkewNode{ x }, root );
  }

  void deleteMin( )
  {
    if( isEmpty( ) )
      throw std::underflow_error( "Could not deleteMin from Empty Heap." );

    mySkewNode *oldRoot = root;
    root = merge( root->left, root->right );
    delete oldRoot;
  }

  void deleteMin( Comparable & minItem )
  {
    minItem = findMin( );
    deleteMin( );
  }

  void makeEmpty( )
  {
    root = nullptr;
  }

  void merge( mySkewHeap & rhs )
  {
    if( this == &rhs )  // Avoid aliasing problems
      return;
    root = merge( root, rhs.root );
    rhs.root = nullptr;
  }

  void printPreOrder( void )
  {
    if( root != nullptr )
    {
      std::cout << root->element << ' ';
      printPreOrder( root->left );
      printPreOrder( root->right );
    }
    std::cout << '\n';
  }

private:
  struct mySkewNode
  {
    Comparable   element;
    mySkewNode *left;
    mySkewNode *right;
    int          npl;

    mySkewNode( const Comparable & e, mySkewNode *lt = nullptr,
      mySkewNode *rt = nullptr, int np=0 )
      : element{ e }, left{ lt }, right{ rt }, npl{ np }{ }

    mySkewNode( Comparable && e, mySkewNode *lt = nullptr,
      mySkewNode *rt = nullptr, int np=0 )
      : element{ std::move( e ) }, left{ lt }, right{ rt }, npl{ np }{ }
  };

  mySkewNode *root;

  mySkewNode * merge( mySkewNode *h1, mySkewNode *h2 )
  {
    if( h1 == nullptr )
      return h2;
    if( h2 == nullptr )
      return h1;
    if( h1->element < h2->element )
      return merge1( h1, h2 );
    else
      return merge1( h2, h1 );
  }

  mySkewNode * merge1( mySkewNode *h1, mySkewNode *h2 )
  {
    if( h1->left == nullptr )   // Single node
      h1->left = h2;            // Other fields in h1 already accurate
    else
    {
      h1->right = merge( h1->right, h2 );
      // if( h1->left->npl < h1->right->npl )
      swapChildren( h1 );
      h1->npl = h1->right->npl + 1;
    }
    return h1;
  }

  void swapChildren( mySkewNode *t )
  {
    mySkewNode *temp = t->right;
    int tempNpl = t->right->npl;

    t->right = t->left;
    t->right->npl = t->left->npl;

    t->left = temp;
    t->left->npl = tempNpl;
  }

  void printPreOrder( mySkewNode *t )
  {
    if( t != nullptr )
    {
      std::cout << t->element << ' ';
      printPreOrder( t->left );
      printPreOrder( t->right );
    }
  }

  // void reclaimMemory( mySkewNode *t ) { }
  // mySkewNode * clone( mySkewNode *t ) const { }

};

#endif
