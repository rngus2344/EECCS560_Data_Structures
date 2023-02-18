# include "myVector.h"
# include <iostream>
# include <vector>
# include <fstream>
# include <string>

using namespace std;

void readInstances(const string& line_data, vector<string>& store_data)
{
    int pos = 0; 
    int front = 0;
    while(front < line_data.size())
    {
        if(line_data[front] ==' ')
        {
            store_data.push_back(line_data.substr(pos,front-pos));
            pos=front+1;
        }
        front++;
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Please provide a test instance file!" <<endl;
        return 0;
    }

    ifstream f_input;
    f_input.open(argv[1]);	
    vector<string> data;
    if (0 == f_input.is_open())	    
    {
        cout << "Error for opening the test instance file!"<<endl;
        return 0;
    }
    else
    {
        string line;
        while(getline(f_input, line))
        {
            readInstances(line,data);
            /**
             * This is a test for construct using STL vector
             * myVector(const vector<Object>& data)
             * 0, empty test 
             * 1, Find value[size/2]
             * 
            */
            myVector<string> m_vector1(data);
            cout << m_vector1.empty()<<endl;
            cout << m_vector1[m_vector1.size()/2] << endl;
            for (int i = (m_vector1.size()-1)/2; i >= 0; i--)
            {
                cout<<m_vector1[i]<<" ";
            }
            cout << endl;
            /**
             *  This is a test for construct using push_back
             *  push_back(const Object& x)
             *  para: const Object& x
             *  return void
            */
            myVector<string> m_vector2;
            for(int i = data.size() - 1; i >= 0 ; i--)
            {
                m_vector2.push_back(data[i]);
            } 
            for(auto x : m_vector2) 
            {
                cout << x << " ";
            }
            cout << endl;
            /**
             *  This is a test for construct using append
             *  myVector<Object>& append(const myVector<Object>& data)
             *  para: const myVector<Object>& data
             *  return void
            */
            myVector<string> m_vector3(m_vector1);
            for(int i = 0; i < m_vector3.size()/2; i++) 
            {
                m_vector3.pop_back();
            } 
            m_vector3 = m_vector3.append(m_vector1);
            m_vector3 = m_vector3.append(m_vector2);
            for(auto x : m_vector3) 
            {
                cout << x << " ";
            }
            cout << endl;
        }
    }

    return 1;
}