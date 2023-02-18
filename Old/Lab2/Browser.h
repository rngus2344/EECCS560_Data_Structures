/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file Browser.h
* @date 6/26/2020
* @brief header file of Browser
 ---------------------------------------------------------------------------- */
//Start your program.
#ifndef BROWSER_H
#define BROWSER_H

#include "BrowserHistoryInterface.h"
#include "LinkedList.h"

class Browser: public BrowserHistoryInterface
{
private:
  LinkedList<std::string> m_url;

public:
  /**
  * @post All memory allocated by the implementing class should be freed.
  *       This, as with all virtual destrucors, is an empty definition since we
  *       have no knowledge of specific implementation details.
  */
  ~Browser();

  /**
  * @pre none
  * @post the browser navigate to the given url
  * @param url, a string representing a URL
  */
  void navigateTo(std::string url);

  /**
  * @pre none
  * @post if possible, the browser navigates forward in the history otherwise it keeps focus
  *       on the current URL
  */
  void forward();

  /**
  * @pre none
  * @post if possible, the browser navigates backwards in the history otherwise it keeps focus
  *       on the current URL
  */
  void back();

  /**
  * @return the current URL
  */
  std::string current() const;

  /**
  * @pre The list being passed in is empty
  * @post The current browser history is copied into the given list
  * @param destination, an empty list of strings
  */
  void copyCurrentHistory(ListInterface<std::string>& destination);

  void printHistory();
};

#endif
