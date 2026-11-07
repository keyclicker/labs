#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
  double eps;

  cin >> eps;

  double a = 0, b = 1, fac = 1, d, sum = 0;
  for (int i = 1; ; i++)
  {
    fac *= i;

    d = b / fac;
    sum  += d;

    if (d < eps) break;

    auto tmp = a + b;
    a = b; b = tmp;
  }

  cout << sum << endl;
}