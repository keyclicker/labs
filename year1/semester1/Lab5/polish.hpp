#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

double reverse_polish(string expr);
string to_polish(string expr);

bool is_operator(char val);

inline double calculate(const string &expr)
{
  return reverse_polish(to_polish(expr));
}