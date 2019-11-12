#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

double reverse_polish(const string &expr);
string to_polish(string expr);

bool is_operator(const char val);