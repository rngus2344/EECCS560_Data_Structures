/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file Executive.h
* @date 6/26/2020
* @brief header file of Executive
 ---------------------------------------------------------------------------- */
//Start your program.
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "Browser.h"
#include <string>

class Executive
{
private:
  Browser browser;

public:
  /**
  * @pre None
  * @post Creates queue and stack with the data from the file and print what it needs to print.
  * @param fileName, name of the file to open
  * @throw None
  **/
  Executive();
};

#endif
