#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>
using namespace std;

using Long = long long;

int main()
{
  Long n;
  cin >> n;

  vector<int> arr(n);

  for (auto &a : arr)
    cin >> a;

  bool k = false;
  bitset<64> bit;

  for (Long i = 0; i < pow(2, n); i++)
  {
    bit = i;
    int a = 0;
    for (int j = 0; j < n; j++)
    {
      a += (bit[j] ? 1 : -1) * arr[j];
    }
    if (!a)
    {
      k = true;
      break;
    }
  }

  if (k)
  {
    for (int j = 0; j < n; j++)
    {
      cout << (bit[j] ? "" : "-") << arr[j] << ' ';
    }
    cout << endl;
  }
  else
  {
    cout << "NIT";
  }
}