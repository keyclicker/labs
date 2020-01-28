#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
  int n = 50;
  cin >> n;

  ifstream in("../in.txt");
  ofstream out("../out.txt");

  string str;
  while (!in.eof())
  {
    getline(in, str);

    auto s = str.size();
    if (s < n)
    {
      for (int i = 0; 2 * i + s < n; i++)
      {
        str.insert(str.begin(), ' ');
      }
    }
    cout << str << endl;
    out << str << endl;
  }



}