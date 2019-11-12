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

    if (is_operator(token[0]) || token == ">=" || token == "<=")
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
          opStack.push(a <= b);
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

string to_polish(string expr)
{
 // auto i = expr.begin();
 // while (i < expr.end() );



  for (auto i = expr.begin(); i < expr.end(); ++i)
  {
    if (is_operator(*i))
    {
      expr.insert(i, ' ');

      i += 2;
      if (*i == '=') ++i;

      //if (i == expr.end()) break; //end() updating, so i can't set it to the loop head

        expr.insert(i, ' ');
    }
    ++i;
  }

  return expr;
}

bool is_operator(const char val)
{
  return (
    val == '+' || val == '-' ||
    val == '*' || val == '/' ||
    val == '&' || val == '|' ||
    val == '>' || val == '<' || val == '=' ||
    val == ')' || val == '('
  );
}