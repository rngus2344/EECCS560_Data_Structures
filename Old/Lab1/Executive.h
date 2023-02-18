/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file Executive.h
* @date 6/26/2020
* @brief header file of Executive
 ---------------------------------------------------------------------------- */
//Start your program.
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "LinkedList.h"
#include <string>

class Executive
{
private:
  LinkedList<int> m_list;

public:
  /**
  * @pre None
  * @post Creates queue and stack with the data from the file and print what it needs to print.
  * @param fileName, name of the file to open
  * @throw None
  **/
  Executive(std::string fileName);
};

#endif
