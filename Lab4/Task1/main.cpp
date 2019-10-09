#include <iostream>
#include <string>
using namespace std;

string getPalindrom(const string &str)
{
  auto last = str.back();
  auto pivot = str.size() - 1;

  for (int i = 0; i < str.size() - 1; ++i)
  {
    if (str[i] == last)
    {
      bool isp = true;
      for (int j = i + 1; j < (str.size() + i) / 2; ++j)
      {
        if (str[j] != str[str.size() - j - 1])
        {
          isp = false;
          break;
        }
      }

      if (isp)
      {
        pivot = i;
        break;
      }
    }
  }

  string add;
  add.reserve(str.size() - pivot - 1);

  for (int i = 0; i < pivot; ++i)
  {
    add.push_back(str[pivot - i - 1]);
  }

  return str + add;
}

int main()
{
  string str;
  cin >> str;

  cout << getPalindrom(str);
}