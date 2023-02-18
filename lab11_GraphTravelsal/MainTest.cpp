
#include <stack>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cstring>
#include <algorithm> 
#include <sstream>   
#include "myGraph.h"
using namespace std;

class CitiesEntry
{
    public:
        string city_a;
        string  city_b;
        int distance;
        CitiesEntry(){}
        CitiesEntry( string a,  string b, int c)
        {
            city_a = a;
            city_b = b;
            distance = c;
        }

};
//get first line and split the string by pattern
vector<string> split(const string &str, const string &pattern)
{
    vector<string> res;
    if(str == "")
        return res;
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}
// read data file from specific line
ifstream & seek_to_line(ifstream & in, int line)
{
    int i;
    char buf[1024];
    in.seekg(0, ios::beg);  
    for(i = 0; i < line; i ++)
    {
        in.getline(buf, sizeof(buf));
    }
    return in;
}

int main(int argc, char* argv[])
{

    if (argc != 2)
    {
        std::cout << "You have to provide one test data file and output file name to run the MainTest!\n";
        return 0;
    }
    
    std::ifstream ifstrm(argv[1], std::ios_base::in);
    if (!ifstrm) 
    {
        std::cerr << "Cannot open file: " << std::endl;
        exit (1);
    }
    vector<string> city_nodes;
    myGraph mg;
    string line;
    string line_1;
   // CitiesEntry for data file (city a, city b, distance)
    vector<CitiesEntry> v_id;
    map<string, int > city_map;
    //get first line to generate the city map
    getline (ifstrm,line_1);
    city_nodes = split(line_1," ");
    for (size_t i = 0; i < city_nodes.size(); i++)
    {
       int id = mg.addNode(city_nodes[i]);
       city_map.insert(make_pair(city_nodes[i],id));
    }
    //read from the 1 line
    seek_to_line(ifstrm,1);
    //get CitiesEntry(city_a, city_b, distance)
    while (getline(ifstrm,line)) 
    {
       std::istringstream iline(line);
       string city;
       string city_b;
       int distance;
       iline >> city >> city_b >> distance;
       CitiesEntry ce(city,city_b,distance);
       v_id.push_back(ce);
    }
    //add edge by sample_input data format
    for (size_t i = 0; i < v_id.size(); i++)
    {
        EdgeType et(v_id[i].distance);
        int id1 = city_map[v_id[i].city_a];
        int id2 = city_map[v_id[i].city_b];
        mg.addEdge(et,id1,id2);
    }
    //connect 1 to end
    vector<string> path_bfs;
    vector<string> path_dfs;
    //test bfs
    mg.BFS(1,path_bfs);
    //test dfs
    mg.DFS(1,path_dfs);
    vector<string> path_sp;
    //test shortest path from 1 to mid of city map
    int min = mg.shortestPath(1,city_map.size()/2,path_sp);
    for (size_t i = 0; i < path_bfs.size(); i++)
    {
        cout<<path_bfs[i]<<" ";
    }
    cout<<endl;
    for (size_t i = 0; i < path_dfs.size(); i++)
    {
        cout<<path_dfs[i]<<" ";
    }
    cout<<endl;
    for (size_t i = 0; i < path_sp.size(); i++)
    {
        cout<<path_sp[i]<<" ";
    }
    cout<<endl;
    cout<<min<<endl;
    
    return 1;
}

    
