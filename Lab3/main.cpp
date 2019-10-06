#include "GraphBuilder.hpp"
#include "fourier.hpp"

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  GraphBuilder gb(1920, 1080);


  auto f = [] (double x)
  {
//    return 1*abs(sin(x))/sin(x);
//    return sin(x);
//      return x*x;
    return 2.0*(x - floor(x))-1.0;
  };

  gb.addFunc(f);
  gb.addFunc([f] (double x) {return fourier(f, x, 10);});

  gb.run();
}
