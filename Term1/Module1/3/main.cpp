#include <iostream>
#include <cstdio>
#include <list>
#include <algorithm>
using namespace std;

struct strs
{
  int a, b;
};

list<strs> ls;

int main()
{
  char str[256];
  cin.getline(str, 256);

  int size = 0;

  while (str[size] != '\0') size++;

  for (int i = 0; i < size; i++)
  {
    for (int j = i + 1; j < size; j++)
    {
      bool isp = true;
      int a = i, b = j;

      for (; a < b; ++a, --b)
      {
        if (str[a] != str[b])
        {
          isp = false;
          break;
        }
      }

      if (isp)
      {
        ls.emplace_back(strs{i, j});
      }
    }
  }

  for (auto i = ls.begin(); i != ls.end(); i++)
  {
    for (auto j = ls.begin(); j != ls.end(); j++)
    {
      if (i->a >= j->a && i->b <= j->b && i != j)
        i->b = -1;
    }
  }

  ls.sort([](strs a, strs b)
  {
    return (a.b - a.a) > (b.b - b.a);
  });

  for (auto a : ls)
  {
    if (a.b != -1)
    {
      for (int i = a.a; i <= a.b; i++)
        cout << str[i];
      cout << endl;
    }
  }
}