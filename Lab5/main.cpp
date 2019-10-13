#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <set>

float reverse_polish(const std::string &expr)
{
  std::stringstream stream;
  stream << expr;

  std::stack<char> opStack;

  while (!stream.eof())
  {
    std::string token;
    stream >> token;

    if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
    {
      if (opStack.size() >= 2)
      {
        auto b = opStack.top();
        opStack.pop();
        auto a = opStack.top();
        opStack.pop();

        switch (token[0])
        {
          case '+':
            opStack.push(a + b);
            break;
          case '-':
            opStack.push(a - b);
            break;
          case '*':
            opStack.push(a * b);
            break;
          case '/':
            opStack.push(a / b);
            break;
        }
      }
      else throw std::logic_error("Wrong operands count");
    }
    else
    {
      try
      {
        opStack.push(stof(token));
      }
      catch (...)
      {
        throw std::logic_error("Wrong operand or operator: '" + token +"'");
      }
    }
  }

  return opStack.top();
}



int main()
{
  std::string expr;
  getline(std::cin, expr);

  std::cout << reverse_polish(expr);
}