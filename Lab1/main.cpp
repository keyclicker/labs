#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

#include "integer.hpp"

int main()
{
  Integer ai;
  Integer bi;

  for (;;)
  {
    long long a, b;

    cin >> a >> b;

    ai = Integer(a);
    bi = Integer(b);

    cout << int(ai) << endl;
  }
}
