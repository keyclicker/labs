#include "lab.hpp"
#include "polish.hpp"

#include <map>
#include <sstream>

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

  //lables marking
  while (!in.eof())
  {
    in >> smnt;
    if (smnt.back() == ':')
    {
      smnt.erase(--smnt.end());
      lables.insert(make_pair(smnt, in.tellg()));
    }
  }

  in.clear();
  in.seekg(0, ios_base::beg);

  while (!in.eof() && smnt != "exit")
  {
    in >> smnt;

    if (smnt == "print")
    {
      string expr;
      getline(in, expr);

      out << reverse_polish(expr) << endl;
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
    else if (smnt == "goto")
    {
      string name;
      in >> name;
      in.clear();
      in.seekg(lables[name], ios_base::beg);
    }
    else if (smnt == "if")
    {
      string ifsnt;
      getline(in, ifsnt);

      ifsnt.erase(ifsnt.begin());
      ifsnt.erase(ifsnt.begin());
      ifsnt.erase(--ifsnt.end());

      if (!reverse_polish(ifsnt))
      {
        string endsearch;
        while (endsearch != "endif")
          in >> endsearch;
      }
    }
  }
}

double* get_var(string name)
{
  return &vars[name];
}
