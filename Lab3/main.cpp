#include "GraphBuilder.hpp"
#include "fourier.hpp"

#include <cmath>
using namespace std;

int main()
{
  GraphBuilder gb(1920, 1080);

  auto f = [] (double x) -> double
  {
    return x*x;
  };

  gb.addFunc(f);
  gb.addFunc([f] (double x) {return fourier(f, x, 10);});

  gb.run();
}
