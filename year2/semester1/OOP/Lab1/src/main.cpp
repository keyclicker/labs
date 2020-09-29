#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

#include "FunctionBuilder/FunctionBuilder.hpp"
#include "Shape.hpp"
#include "Graph.hpp"

int main() {
  //FunctionBuilder gb(1920, 1080);
  //gb.run();

  auto s = Shape([](auto x){return cos(x);}, [](auto x){return -cos(x);});

  auto area = s.getArea(-3.1415/2.0, 3.1415/2.0);
  cout << area << endl;
}
