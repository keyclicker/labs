#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <set>
using namespace std;

float polish(const string &expr)
{
  stringstream stream;
  stream << expr;

  stack<char> opStack;
  queue<float> nums;

  while (!stream.eof())
  {
    string token;
    stream >> token;

    if (token == "+" || token == "-" || token == "*" || token == "/")
      opStack.push(token[0]);
    else
      nums.push(stof(token));
  }

  while (!opStack.empty())
  {
    auto op = opStack.top();
    opStack.pop();

    auto a = nums.front(); nums.pop();
    auto b = nums.front(); nums.pop();

    switch (op)
    {
      case '+':
        nums.push(a + b);
        break;
      case '-':
        nums.push(a - b);
        break;
      case '*':
        nums.push(a * b);
        break;
      case '/':
        nums.push(a / b);
        break;
    }
  }

  return nums.front();
}



int main()
{
  string expr;
  getline(cin, expr);

  cout << polish(expr);
}