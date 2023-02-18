#include <iostream>
#include <string>

std::string func(std::string & p)
{
  return p;
}

int main()
{
  std::string str = "nam";
  // int i = 12;
  std::cout << func("nam") << '\n';
  return(0);
}
