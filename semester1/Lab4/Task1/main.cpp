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
  auto i = str.size();

  for (; i >= 0; --i)
  {
    if (isPalindrom(str.begin(), str.begin() + i)) break;
  }

  cout << str + str.substr(i, str.size());
}

int main()
{
  string str;
  cin >> str;

  cout << isPalindrom(str.begin(), str.end());
}