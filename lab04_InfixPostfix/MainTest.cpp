
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "myInfixCalculator_g491n054.h"

using namespace std;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
      if (argc != 2)
      {
            std::cout << "You have to provide one test instance file and output file name to run the test main!\n";
            return 0;
      }
      ifstream inFile;
      inFile.open(argv[1]);
      myInfixCalculator mip;
      if (inFile.is_open())
      {
            string str;
            while (std::getline(inFile, str))
            {
                vector<string> data;
                mip.tokenize(str,data);
                cout<<data.size()<<endl;
                cout<<str<<endl;
                string s = mip.infixToPostfix(str);
                cout<<s<<endl;
                int num = mip.calculatePostfix(s);
                cout<<num<<endl;
                cout<<endl;
            }
      }
      else
      {
            cout << "The instance.txt file cannot be opened";
      }
      inFile.close();

    return 1;
}
