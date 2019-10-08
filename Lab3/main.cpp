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
//    return x*x;
    return 2.0*(x - floor(x))-1.0;
//    return 1.0/x;
//    return sin(1.3*x);
  };

  //cout << integral(-1, 1, f);

  gb.addFunc(f);
  gb.addFunc([f](double x){return fourier(f, x, 100);});
//  gb.addFunc([f](double x){return sin(1.3*x);});

//  gb.addFunc([](double x){return sin(x);});
//  gb.addFunc([](double x){return cos(x);});
//  gb.addFunc([f] (double x) {return fourier(f, x, 10);});

  gb.run();
}
