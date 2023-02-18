/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file Executive.cpp
* @date 6/26/2020
* @brief cpp file of Executive
 ---------------------------------------------------------------------------- */
//Start your program.
#include "Executive.h"
#include <iostream>
#include <fstream>
#include <string>

Executive::Executive(std::string fileName)
{
  int entry;

  std::ifstream inFile;

  inFile.open(fileName);
  if(inFile.fail())
  {
    std::cout << "Opening file has failed. \n";
  }
  else
  {
    while(inFile >> entry)
    {
      m_list.insert(entry, m_list.getLength()+1);
    }

    do
    {
      int option;

      std::cout << "-------------------------------------------------------------\n\n";
      std::cout << "Choose one operation from the options below: \n\n";
      std::cout << "  1. IsEmpty\n  2. Length\n  3. Insert\n  4. Delete\n  5. Find\n";
      std::cout << "  6. FindPrev\n  7. AppendList\n  8. ForwardTraverse\n  9. BackwardTraverse\n  10. Exit\n\n";
      std::cout << "> ";
      std::cin >> option;
      std::cout << '\n';

      if(option == 1)
      {
        if(m_list.isEmpty())
        {
          std::cout << "> The list is empty.\n\n";
        }
        else
        {
          std::cout << "> The list is not empty.\n\n";
        }
      }
      else if(option == 2)
      {
        std::cout << "The length of the list is: " << m_list.getLength() << "\n\n";
      }
      else if(option == 3)
      {
        int num1;
        std::cout << "Choose a number to be inserted:\n\n> ";
        std::cin >> num1;
        if(m_list.find(num1))
        {
          std::cout << "> Number already exists. Cannot insert.\n\n";
        }
        else
        {
          m_list.insert(num1, m_list.getLength()+1);
          std::cout << "\n> " << num1 << " is inserted.\n\n";
        }
      }
      else if(option == 4)
      {
        std::cout << "Option 4\n";
        int num2;
        std::cout << "Choose a number to be deleted from the list:\n\n> ";
        std::cin >> num2;
        if(m_list.find(num2))
        {
          m_list.delete(num2);
          std::cout << "\n> " << num2 << " is deleted from the list.\n\n";
        }
        else
        {
          std::cout << "> Number does not exist. Cannot delete.\n\n";
        }
      }
      else if(option == 5)
      {
        std::cout << "Option 5\n";
        int num3;
        std::cout << "Enter the number to find:\n\n> ";
        std::cin >> num3;
        if(m_list.find(num3))
        {
          std::cout << "\n> " << num3 << " is found in the list.\n\n";
        }
        else
        {
          std::cout << "\n> " << num3 << " is not found in the list.\n\n";
        }
      }
      else if(option == 6)
      {
        std::cout << "Option 6\n";
      }
      else if(option == 7)
      {
        // int num4;
        // std::cout << "Enter list to append:\n\n> ";
        //
        // std::cin >> num4;
        // m_list.insert(num4, m_list.getLength()+1);

        std::cout << "\n> List appended.\n\n";
      }
      else if(option == 8)
      {
        std::cout << "> Forward Traverse: ";
        m_list.forwardTraverse();
        std::cout << "\n";
      }
      else if(option == 9)
      {
        std::cout << "> Backward Traverse: ";
        m_list.backwardTraverse();
        std::cout << "\n";
      }
      else if(option == 10)
      {
        std::cout << "> Program execution completed!\n\n";
        break;
      }
      else
      {
        std::cout << "Wrong input\n";
      }
    } while(1);
  }
  inFile.close();
}
