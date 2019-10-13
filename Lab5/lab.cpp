#include "lab.hpp"
#include "vars.hpp"
#include "polish.hpp"

void interactive_mode()
{
  lab_start(cin, cout);
}

void script_mode(string file_path)
{

}

void lab_start(istream &in, ostream &out)
{
  string smnt; //statement

  while (smnt != "exit")
  {
    in >> smnt;

    if (smnt == "print")
    {
      string expr;
      getline(in, expr);

      cout << reverse_polish(expr) << endl;
    }
    else if (smnt[0] == '$')
    {
      smnt.erase(smnt.begin());
      auto var = alloc_var(smnt);

      char eq;
      cin >> eq;

      if (eq != '=') throw logic_error("Wrong statement");

      string expr;
      getline(in, expr);

      *var = reverse_polish(expr);
    }
  }
}