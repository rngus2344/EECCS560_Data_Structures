/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file Browser.cpp
* @date 6/26/2020
* @brief cpp file of Browser
 ---------------------------------------------------------------------------- */
//Start your program.
#include "Browser.h"
#include <string>
#include <iostream>

Browser::~Browser()
{

}

void Browser::navigateTo(std::string url)
{
  m_url.insert(url, 1);
}

void Browser::forward()
{

}

void Browser::back()
{
  // copy.remove(1);
}

std::string Browser::current() const
{
  return(m_url.getEntry(1));
}

void Browser::copyCurrentHistory(ListInterface<std::string>& destination)
{

}

void Browser::printHistory()
{
  for(int i=m_url.getLength(); i>=1; i--)
  {
    std::cout << m_url.getEntry(i);
    std::cout << '\n';
  }
}
