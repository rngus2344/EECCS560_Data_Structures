
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "myQueue.h"
#include "myStack.h"
using namespace std;
using std::cout;
using std::endl;

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
            const int capicity_size = 10;
            //1. 2. Test constructor myStack(const int& size)
            myStack<string> my_stack1(capicity_size);
            myQueue<string> my_queue1(capicity_size);
            //7, push(), enqueue(), reserve()
            for (int i = 0;i < data.size(); ++i)
            {
                my_stack1.push(data[i]);
                my_queue1.enqueue(data[i]);
            }
            //9 , 10 , 11
            cout<<my_stack1.empty()<<endl;
            cout<<my_queue1.empty()<<endl;
            cout<<my_stack1.size()<<endl;
            cout<<my_queue1.size()<<endl;
            cout<<my_stack1.top()<<endl;
            cout<<my_queue1.front()<<endl;
            cout<<my_stack1.top()<<endl;
            cout<<my_queue1.front()<<endl;
            //4 
            myStack<string> my_stack2(my_stack1);
            myQueue<string> my_queue2(my_queue1);
            my_queue2.dequeue();
            my_stack2.pop();
            cout<<my_stack2.size()<<endl;
            cout<<my_queue2.size()<<endl;
            //8
            my_queue2.dequeue();
            //8
            my_stack2.pop();
            //5
            myQueue<string> my_queue3 = my_queue2;
            myStack<string> my_stack3 = my_stack2;
            //9
            my_queue3.enqueue(my_queue2.front());
            cout<<""<<my_queue3.size()<<endl;
            cout<<""<<my_stack3.size()<<endl;
        }
    }

    return 1;
}
