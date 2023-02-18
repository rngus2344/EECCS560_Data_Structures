#include <string>
#include <vector>
#include <utility> 
#include <algorithm>
#include <iostream>
#include <iterator>
#include<bits/stdc++.h>
#include "myMaze.h"
#include "myDisjointSets.h"
using namespace std;

bool pathCheck(vector<int>& path,vector<pair<int, int> > broken_walls)
{
    vector<pair<int, int> >::iterator it;
    pair<int,int> tmp_pair;
    int count = 0;
    for (size_t i = 0; i < path.size(); i++)
    {
        if(i+1<path.size())
        {
            if( path[i]< path[i+1])
            {
                tmp_pair = make_pair(path[i],path[i+1]);
            }
            else
            {
                tmp_pair = make_pair(path[i+1],path[i]);
            }
            it = find (broken_walls.begin(), broken_walls.end(), tmp_pair);
            if(it != broken_walls.end())
            {
                ++count;
            } 
        }
    }
    if((path.size()-1) == count)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char* argv[])
{
      if (argc != 2)
      {
            std::cout << "You have to provide one test data file and output file name to run the MainTest!\n";
            return 0;
      }
      
      ifstream inFile;
      inFile.open(argv[1]);
      vector<int> tmp;
      if (inFile.is_open())
      {
            int str;
            while(!inFile.eof())
            {
                inFile >> str;
                tmp.push_back(str);
            }

            //test myMaze
            int col = tmp[1]%10;
            int row = tmp[2]%10;
            myMaze m1(col,row);
            vector<pair<int, int> > broken_walls;
            vector<int> path;
            m1.buildMaze(broken_walls);
            m1.solveMaze(path);
            vector<int> path_vaild;
            //check valid path
            cout<<pathCheck(path,broken_walls)<<endl;
            //check path duplicate element
            bool duplicate = std::set<int>(path.begin(), path.end()).size() != path.size();
            cout<<duplicate<<endl;
            //check entrance and exit
            if (path[0] == 0 && path[path.size()-1] == row*col - 1)
            {
                    cout << "1" << endl;
            }
            else
            {
                    cout << "0" << endl;
            }
            //check path size
            if((col+(row))- 1 <= path.size() <= col*(row))
            {
                cout << "1" << endl;
            }else
            {
                cout << "0" << endl;
            }
      }
      else
      {
            cout << "The data file cannot be opened";
      }
      inFile.close();
    
    return 1;
}

