#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void interactive_mode();
void script_mode(string file_path);
void lab_start(istream &in, ostream &out);

//void statement_processor(string smnt);

double* alloc_var(string name);
double* get_var(string name);
