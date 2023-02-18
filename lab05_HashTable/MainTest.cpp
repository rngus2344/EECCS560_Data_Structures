
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "myHashTable.h"

using namespace std;
using std::cout;
using std::endl;

class HashEntry
{
    private:
       string key_;
       size_t value_;
    public:
        HashEntry()
        {

        }
        HashEntry(const string& key, const size_t& val)
        {
          this->key_ = key;
          this->value_ = val;
        }

        const string getKey() const
        {
            return this->key_;
        }
        size_t getValue()
        {
          return this->value_;
        }

        bool operator ==(const HashEntry& p) const
        {
            return (this->key_ == p.key_);
        }

  };



int main(int argc, char* argv[])
{
      if (argc != 2)
      {
            std::cout << "You have to provide one test instance file and output file name to run the test main!\n";
            return 0;
      }
      ifstream inFile;
      inFile.open(argv[1]);
      myHashTable<HashEntry> hash_entry;
      myHashTable<string> hash_n;
      string tmp;
      if (inFile.is_open())
      {
            string str;
            while (std::getline(inFile, str))
            {
                HashEntry* hent = new HashEntry[str.size()];
                for (size_t i = 0; i < str.size()-5; i++)
                {
                 hent[i] = HashEntry(str.substr(i,5),hash_n.strToHashValue(str.substr(i,5)));
                 hash_entry.insert(hent[i]);
                }

                //Test insert function
                tmp = str;

                //(key, value)
                HashEntry he(tmp.substr(0,10),hash_n.strToHashValue(tmp.substr(0,10)));
                HashEntry he1(tmp.substr(1,10),hash_n.strToHashValue(tmp.substr(1,10)));
                HashEntry he2(tmp.substr(2,10),hash_n.strToHashValue(tmp.substr(2,10)));
                HashEntry he3(tmp.substr(3,10),hash_n.strToHashValue(tmp.substr(3,10)));
                HashEntry he4(tmp.substr(0,10),hash_n.strToHashValue(tmp.substr(0,10)));

                cout<<he.getKey()<<" "<<he.getValue()<<endl;
                cout<<he1.getKey()<<" "<<he1.getValue()<<endl;
                cout<<he2.getKey()<<" "<<he2.getValue()<<endl;
                cout<<he3.getKey()<<" "<<he3.getValue()<<endl;
                cout<<he4.getKey()<<" "<<he4.getValue()<<endl;

                hash_entry.insert(he);
                hash_entry.insert(he1);
                hash_entry.insert(he2);
                hash_entry.insert(he3);
                hash_entry.insert(he4);

                // Test contains
                bool mid_element = hash_entry.contains(he2);
                cout<<""<<mid_element<<endl;
                //Test remove function
                bool remove_mid_1 = hash_entry.remove(he2);
                cout<<""<<remove_mid_1<<endl;
                bool mid_element_1 = hash_entry.contains(he2);
                cout<<""<<mid_element_1<<endl;
                bool mid_element_2 = hash_entry.contains(he1);
                cout<<""<<mid_element_2<<endl;
                //Test strToHashValue
                cout<<""<<hash_n.strToHashValue(tmp)<<endl;

                const char* c_tmp = tmp.c_str();
                int m = (int)c_tmp[0];
                int a = (int)c_tmp[str.size()-1];
                int b = (int)c_tmp[str.size()-2];
                int x = (int)c_tmp[str.size()-3];
                //Test universalHash function
                int uni_hash = hash_n.universalHash(x,a,b,m);
                cout<<""<<uni_hash<<endl;
                //delete hent;

            }

      }
      else
      {
            cout << "The instance.txt file cannot be opened";
      }
      inFile.close();

    return 1;
}
