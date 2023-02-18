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


int main(int argc, char **argv )
{
    std::ifstream input(argv[1]);
    std::string line, name, content;
    vector<string> fragments;
    while( std::getline( input, line ).good() )
    {
        if( line.empty() || line[0] == '>' )
        { // Identifier marker
            if( !name.empty() )
            { // output what we read from the last entry
                fragments.push_back(content);
                name.clear();
            }
            if( !line.empty() ){
                name = line.substr(1);
            }
            content.clear();
        } 
        else if( !name.empty() )
        {
            if( line.find(' ') != std::string::npos )
            { // Invalid sequence--no spaces allowed
                name.clear();
                content.clear();
            } else 
            {
                content += line;
            }
        }
    }
    if( !name.empty() )
    { // output what we read from the last entry
        fragments.push_back(content);
        
    }
    myGraph mg;
    string assembly;
    mg.assembleFragments(fragments,assembly);
    cout<<assembly << endl;
    return 0;
}