#include <functional>
#include <cmath>

using namespace std;

//bad fourier
double fourier(const std::function<double(double)> &f, double x,  int n)
{
  //integral detailization
  static constexpr int id = 10;

  static auto a = [f] (int i)
  {
    double res = 0;
    for (int j = 0; j < id - 1; j++)
    {
      double x1 = (double) j/id * M_PI;
      double x2 = (double) (j+1)/id * M_PI;
      res += (x2-x1)*(f(x2) * cos(i*x2) - f(x1) * cos(i*x1));
    }
    return 1.0/M_PI * res;
  };

  static auto b = [f] (int i)
  {
    double res = 0;
    for (int j = 0; j < id - 1; j++)
    {
      double x1 = (double) j/id * M_PI;
      double x2 = (double) (j+1)/id * M_PI;
      res += (x2-x1)*(f(x2) * sin(i*x2) - f(x1) * sin(i*x1));
    }
    return 1.0/M_PI * res;
  };

  double res = a(0) / 2.0;

  for (int i = 0; i < n; i++)
  {
    res += a(n)*cos(n*x) + b(n)*sin(n*x);
  }
}