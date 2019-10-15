#include "polish.hpp"
#include "lab.hpp"

double reverse_polish(const string &expr)
{
  stringstream stream;
  stream << expr;

  stack<double> opStack;

  while (!stream.eof())
  {
    string token;
    stream >> token;

    if (token[0] == '+' || token[0] == '-' ||                         // Yeah,
        token[0] == '*' || token[0] == '/' ||                         // Kinda
        token[0] == '&' || token[0] == '|' ||                         // Bad
        token[0] == '>' || token[0] == '<' || token[0] == '=' ||      // Design
        token == ">=" || token == "<=")                               // KBD (c)
    {
      if (opStack.size() >= 2)
      {
        auto b = opStack.top();
        opStack.pop();
        auto a = opStack.top();
        opStack.pop();

        if (token == ">=")
          opStack.push(a >= b);
        else if (token == "<=")
          opStack.push(a + b);
        else
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
            case '&':
              opStack.push(a && b);
              break;
            case '|':
              opStack.push(a || b);
              break;
            case '>':
              opStack.push(a > b);
              break;
            case '<':
              opStack.push(a < b);
              break;
            case '=':
              opStack.push(a == b);
              break;
          }
      }
      else throw logic_error("Wrong operands count");
    }
    else if (token[0] == '$')
    {
      token.erase(token.begin());
      opStack.push(*get_var(token));
    }
    else
    {
      try
      {
        opStack.push(stof(token));
      }
      catch (...)
      {
        throw logic_error("Wrong operand or operator: '" + token + "'");
      }
    }
  }

  return opStack.top();
}