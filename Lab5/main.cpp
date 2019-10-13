#include "lab.hpp"

int main(int argc, char **argv)
{
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