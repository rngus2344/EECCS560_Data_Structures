
#include <stack>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "myGraph.h"
using namespace std;

int main(int argc, char* argv[])
{
    int id = 0;
    if (argc != 2)
    {
        std::cout << "You have to provide one test data file and output file name to run the MainTest!\n";
        return 0;
    }
    
    vector<string> tmp;
    std::ifstream ifstrm(argv[1], std::ios_base::in);
    if (!ifstrm) 
    {
        std::cerr << "Cannot open file: " << std::endl;
        exit (1);
    }
    myGraph mg;
    string line;
    while (std::getline(ifstrm, line)) 
    {
       tmp.push_back(line);
       NodeType nt(line);
       mg.addNode(nt);
    }
    for (size_t i = 0; i < tmp.size(); i++)
    {
        if (i+2 < tmp.size())
        {
            EdgeType et(i+1);
            mg.addEdge(et,i+1,i+2);
        }
    }
    for (size_t i = tmp.size()-4; i < tmp.size(); i++)
    {
        cout<<i+1<<" "<<mg.getNode(i).city<<"\n";
    }
    for (size_t i = tmp.size()-9; i < tmp.size(); i++)
    {
        if (i+1 < tmp.size())
        {
            cout<<mg.getDegree(i+1)<<" ";
        }
    }
    cout<<endl;
    if (mg.isConnected(tmp.size()-3,tmp.size()-4))
    {
        cout<<"1"<<endl;
    }
    else
    {
        cout<<"0"<<endl;
    }
    mg.deleteNode(tmp.size()-4);
    if (mg.isConnected(tmp.size()-3,tmp.size()-4))
    {
        cout<<"1"<<endl;
    }
    else
    {
        cout<<"0"<<endl;
    }
    mg.deleteEdge(tmp.size()-6,tmp.size()-5);
    cout<<mg.getDegree(tmp.size()-6)<<endl;
    return 1;
}

    
