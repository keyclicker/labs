#include <functional>
#include <cmath>

using namespace std;
using Function = std::function<double(double)>;

double integral(double start, double end, const Function &f)
{
  //integral detailization
  static constexpr int id = 10;

  double res = 0;
  double step = (end-start) / id;

  for (double x = start; x < end; x += step)
  {
    res += (step)*(f(x)+f(x+step))/2.0;
  }
  return res;
}

//bad fourier
double fourier(const Function &f, double x,  int n)
{
  static auto a = [f] (int n)
  {
    auto af = [f, n] (int x) {return f(x)*cos(n*x);};
    return integral(-M_PI, M_PI, af) / M_PI;
  };

  static auto b = [f] (int n)
  {
    auto bf = [f, n] (int x) {return f(x)*sin(n*x);};
    return integral(-M_PI, M_PI, bf) / M_PI;
  };

  double res = a(0) / 2.0;

  for (int i = 1; i < n; i++)
  {
    res += a(i)*cos(i*x) + b(i)*sin(i*x);
  }
}