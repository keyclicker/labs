#include "polish.hpp"
#include "lab.hpp"
#include <stack>
#include <map>

//priority map
map<char, int> pmap = {
        {'*', 4}, {'/', 4},
        {'+', 3}, {'-', 3},
        {'>', 2}, {'<', 2}, {'=', 2},
        {'(', 1}, {')', 1},
};


double reverse_polish(string expr)
{
  stringstream stream;

  // fucking stl, for some reason reads '' when the last character
  // in string stream is ' ', so I need to clean it up
  while (expr.back()==' ') expr.pop_back();

  stream << expr;

  stack<double> opStack;

  while (!stream.eof())
  {
    string token;
    stream >> token;

    if ((is_operator(token[0]) && token.size() == 1) || token == ">=" || token == "<=")
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
  for (auto i = 0; i < expr.size(); ++i)
  {
    if (is_operator(expr[i]))
    {
      expr.insert(expr.begin()+i, ' ');

      i += 2;
      if (expr[i] == '=') ++i;

        expr.insert(expr.begin()+i, ' ');
    }
  }

  stringstream pol;
  stack<string> stk;

  stringstream ss;
  ss << expr;

  string token;
  while (!ss.eof())
  {
    ss >> token;

    if (token[0] == '(')
    {
      stk.push(token);
    }
    else if (token[0] == ')')
    {
      while (stk.top()[0] != '(')
      {
        pol << stk.top() << ' ';
        stk.pop();

        if (stk.empty())
          throw logic_error("Wrong brackets count");  ////////////////////
      }
      stk.pop();
    }
    else if (token[0] == '(')
    {
      stk.push(token);
    }
    else if (token[0] == '-' && (!stk.empty() ? stk.top()[0] == '(' : pol.str() == ""))
    {
      string str;
      ss >> str;

      if (str[0] == '$')
      {
        pol << -(*get_var(str)) << ' ';
      }
      else
      {
        double tmp = stof(str);
        pol << -tmp << ' ';
      }
    }
    else if (is_operator(token[0]))
    {
      if (!stk.empty())
      {
        if (pmap[stk.top()[0]] >= pmap[token[0]])
        {
          pol << stk.top() << ' ';
          stk.pop();
        }
      }

      stk.push(token);
    }
    else
    {
      pol << token << ' ';
    }
  }

  while (!stk.empty())
  {
    pol << stk.top() << ' ';
    stk.pop();
  }

  return pol.str();
}

bool is_operator(char val)
{
  return (
    val == '+' || val == '-' ||
    val == '*' || val == '/' ||
    val == '&' || val == '|' ||
    val == '>' || val == '<' || val == '=' ||
    val == ')' || val == '('
  );
}