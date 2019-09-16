#include "integer.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
  for (;;)
  {
    Integer a, b;
    cin >> a >> b;

    cout << endl;
    cout << "a + b : " << a + b << endl;
    cout << "a - b : " << a - b << endl;
    cout << "a * b : " << a * b << endl;
    cout << "a / b : " << a / (long long)a << endl;

    cout << endl;
    cout << "a == b : " << (a == b) << endl;
    cout << "a != b : " << (a != b) << endl;
    cout << "a <  b : " << (a < b) << endl;
    cout << "a >  b : " << (a > b) << endl;
    cout << "a <= b : " << (a <= b) << endl;
    cout << "a >=  b : " << (a >= b) << endl;

    cout << "\n\n";
  }
}
