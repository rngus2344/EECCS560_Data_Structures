#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "myBinaryHeap.h"
using namespace std;

int main(int argc, char* argv[])
{
      if (argc != 2)
      {
            std::cout << "You have to provide one test data file and output file name to run the MainTest!\n";
            return 0;
      }
      ifstream inFile;
      inFile.open(argv[1]);
      myBinaryHeap<int> mbh;
      myBinaryHeap<int> mbh1;
      vector<int> tmp;
      if (inFile.is_open())
      {
            int str;
            //insert function
            while(!inFile.eof())
            {
                inFile >> str;
                mbh.insert(str);
                tmp.push_back(str);
            }
            mbh.PrintHeap();
            for (size_t i = 0; i < tmp.size()/2; i++)
            {
                mbh1.insert(tmp[i]-1);
            }
            cout<<endl;
            mbh1.PrintHeap();
            cout<<endl;
            mbh.merge(mbh1);
            cout<<mbh.verifyHeapProperty()<<endl;
            cout<<mbh.isEmpty()<<endl;
            cout<<mbh.findMin()<<endl;
            mbh.decreaseKey(1,2);
            mbh.increaseKey(2,8);
            cout<<mbh.verifyHeapProperty()<<endl;
            cout<<mbh.findMin()<<endl;
            mbh.makeEmpty();
            cout<<mbh.isEmpty();
      }
      else
      {
            cout << "The data file cannot be opened";
      }
      inFile.close();
 

    return 1;
}