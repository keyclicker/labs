#include <iostream>
using namespace std;

#include "integer.hpp"

int main()
{
    long long a, b;

    cin >> a >> b;

    Integer ai = a;
//    Integer bi = b;

    cout << ai / b << ' ' << a / b << endl;
}
