/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file LinkedList.h
* @date 6/26/2020
* @brief header file of LinkedList
 ---------------------------------------------------------------------------- */
//Start your program.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include "ListInterface.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList: public ListInterface<T>
{
private:
  Node<T>* m_front;
  int m_length;

public:
  LinkedList();

  LinkedList(const LinkedList<T>& orig);

  ~LinkedList();

  /**
  * @pre The index is valid
  * @post The entry is added to the list at the index, increasing length by 1
  * @param index, position to insert at (1 to length+1)
  * @param entry, value/object to add to the list
  * @throw std::runtime_error if the index is invalid
  */
  void insert(T entry, int index);

  /**
  * @pre The index is valid
  * @post The entry at given position is removed, reducing length by 1
  * @param index, position to insert at (1 to length)
  * @throw std::runtime_error if the index is invalid
  */
  void remove(int index);

  /**
  * @pre The index is valid
  * @post None
  * @param index, position to insert at (1 to length)
  * @throw std::runtime_error if the index is invalid
  */
  T getEntry(int index) const;

  /**
  * @pre The index is valid (must already exist)
  * @post Given entry overrides the entry at the given index
  * @param index, position to override at (1 to length)
  * @param entry, value/object to place at given index
  * @throw std::runtime_error if the index is invalid
  */
  void setEntry(int index, T entry);

  /**
  * @pre None
  * @post List is empty
  * @throw None
  */
  void clear();

  int getLength() const;

  bool isEmpty();
  // void delete(x);
  bool find(T entry);
  // T findPrev(x);
  // void appendList();
  void forwardTraverse();
  void backwardTraverse();
};

#include "LinkedList.cpp"
#endif
