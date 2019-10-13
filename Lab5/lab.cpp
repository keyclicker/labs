#include "lab.hpp"
#include "polish.hpp"

#include <map>

map<string, double> vars;
map<string, int> lables;

void interactive_mode()
{
  lab_start(cin, cout);
}

void script_mode(string file_path)
{
  ifstream fin(file_path);
  lab_start(fin, cout);
}

void lab_start(istream &in, ostream &out)
{
  string smnt; //statement

  while (!in.eof() && smnt != "exit")
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
      auto var = get_var(smnt);

      char eq;
      in >> eq;

      if (eq != '=') throw logic_error("Wrong statement");

      string expr;
      getline(in, expr);

      *var = reverse_polish(expr);
    }
    else if (smnt.back() == ':')
    {
      smnt.erase(--smnt.end());
      lables.insert(make_pair(smnt, in.tellg()));
    }
    else if (smnt == "goto")
    {
      string name;
      in >> name;
      in.seekg(lables[name], ios_base::beg);
    }

  }
}

double* get_var(string name)
{
  return &vars[name];
}
