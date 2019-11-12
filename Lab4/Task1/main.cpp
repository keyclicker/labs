#include <iostream>
#include <string>
using namespace std;

bool isPalindrom(string::const_iterator beg, string::const_iterator end)
{
  --end;
  bool res = true;

  for (;beg <= end; ++beg, --end)
  {
    if (*beg != *end)
    {
      res = false;
      break;
    }
  }
  return res;
}

string getPalindrom(const string &str)
{
  for (int i = str.size() - 1; i > 0; i--)
  {

  }
}

int main()
{
  string str;
  cin >> str;

  cout << isPalindrom(str.begin(), str.end());
}