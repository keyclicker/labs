#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
  ifstream in("incode.cpp");
  ofstream out("outcode.cpp");

  string line;

  while (!in.eof())
  {
    getline(in, line);

    for (auto i = line.begin(); i != line.end() && (*i != '/' || * (i+1) != '/'); ++i)
    {
      out << *i;
    }

    out << endl;
  }
}