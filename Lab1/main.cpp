#include <iostream>
using namespace std;

#include "integer.hpp"

int main()
{
    while (true)
    {
        int a, b;

        cin >> a >> b;

        Integer ai = a;
        Integer bi = b;

        cout << ai - bi << ' ' << a - b << endl;
    }
}
