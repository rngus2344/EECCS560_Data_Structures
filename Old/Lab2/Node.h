/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file Node.h
* @date 6/26/2020
* @brief header file of Node
 ---------------------------------------------------------------------------- */
//Start your program.
#ifndef NODE_H
#define NODE_H

#include <stdexcept>

template <typename T>
class Node
{
private:
	T m_entry;
	Node<T>* m_next;

public:
	/**
	* @pre entry is valid
	* @post Creates a node with m_entry and m_next
	* @param entry is copied on m_entry
	* @throw None
	**/
	Node(T entry);

	/**
	* @pre Stack is non-empty
	* @post Gets m_entry
	* @param None
	* @throw Returns m_entry
	**/
	T getEntry() const;

	/**
	* @pre entry is valid
	* @post Sets m_entry
	* @param entry is copied on m_entry
	* @throw None
	**/
	void setEntry(T entry);

	/**
	* @pre None
	* @post Gets m_next
	* @param None
	* @throw Returns m_next
	**/
	Node<T>* getNext() const;

	/**
	* @pre next is valid
	* @post Sets m_next
	* @param next is copid on m_next
	* @throw None
	**/
	void setNext(Node<T>* next);
};

#include "Node.cpp"
#endif
