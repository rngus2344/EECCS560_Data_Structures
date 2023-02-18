#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "myLeftistHeap.h"
#include "mySkewHeap.h"

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
      myLeftistHeap<int> mlh;
      myLeftistHeap<int> mlh_1;
      mySkewHeap<int> msh;
      mySkewHeap<int> msh_1;
      vector<int> tmp;
      if (inFile.is_open())
      {
            int str;
            //insert function
            while(!inFile.eof())
            {
                inFile >> str;
                mlh.insert(str);
                msh.insert(str);
                tmp.push_back(str);

            }
            for (size_t i = 0; i < tmp.size()/2; i++)
            {
              mlh_1.insert(tmp[i]+1);
              msh_1.insert(tmp[i]+1);
            }
            mlh.merge(mlh_1);
            msh.merge(msh_1);
            cout<<mlh.isEmpty()<<endl;
            cout<<msh.isEmpty()<<endl;

            mlh.printPreOrder();
            msh.printPreOrder();

            cout<<mlh.findMin()<<endl;
            cout<<msh.findMin()<<endl;

            mlh.deleteMin();
            msh.deleteMin();

            mlh.printPreOrder();
            msh.printPreOrder();

            cout<<mlh.findMin()<<endl;
            cout<<msh.findMin()<<endl;

            mlh.makeEmpty();
            msh.makeEmpty();

            cout<<mlh.isEmpty()<<endl;
            cout<<msh.isEmpty()<<endl;
      }
      else
      {
            cout << "The data file cannot be opened";
      }
      inFile.close();
 

    return 1;
}