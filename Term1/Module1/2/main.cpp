#include <iostream>
using namespace std;

int main()
{
  int n;
  cin >> n;

  for (int i = 0; i < n; i++)
  {
    for (int k = 0; k < i; k++)
    {
      for (int m = 0; m < i; m++)
      {
        if (13 * k + 7 * m == i)
        {
          cout << i << ' ';
          goto out;
        }
      }
    }
    out:;
  }
}