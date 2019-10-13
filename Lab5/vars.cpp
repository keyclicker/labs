#include "vars.hpp"
#include <map>

map<string, double> vars;

double* alloc_var(string name)
{
  vars.insert(make_pair(name, 0));
  return &vars[name];
}


double* get_var(string name)
{
  return &vars[name];
}
