#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n;
string val;
void dick()
{
  if (val.size() == 2*n)
  {
    cout << val << endl;
    return;
  }

  if (val.empty())
  {
    val.assign("(");
  }

  if (count(val.begin(), val.end(), '(') != n)
  {
    val.insert(val.end(), '(');
    dick();
    val.erase(val.end()-1);
  }

  if (count(val.begin(), val.end(), '(') > count(val.begin(), val.end(), ')'))
  {
    val.insert(val.end(), ')');
    dick();
    val.erase(val.end() - 1);
  }
}

int main()
{
  cin >> n;
  dick();
}