#include "lab.hpp"
#include "polish.hpp"

int main(int argc, char **argv)
{
  string str;
  cin >> str;
  cout << to_polish(str);


  if (argc == 1)
  {
    interactive_mode();
  }
  else
  {
    for (int i = 1; i < argc; i++)
      script_mode(argv[i]);
  }
}