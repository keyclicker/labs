#include <functional>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using Function = std::function<double(double)>;

//id - integral detailization
double integral(double start, double end, const Function &f, int id)
{
  double res = 0;
  double step = (end-start) / id;

  for (double x = start; x < end; x += step)
  {
    res += (step)*(f(x)+f(x+step))/2.0;
  }
  return res;
}

//template <const Function &f>
double fourier(const Function &f, double x,  int n, double P = M_PI)
{
  static vector<double> a, b;
  a.reserve(n);
  b.reserve(n);

  if (a.size() < n) //&& b.size() < n
  {
    for (int i = a.size(); i < n; ++i)
    {
      auto af = [f, i, P] (double x) {return f(x)*cos(M_PI*i*x/P);};
      auto bf = [f, i, P] (double x) {return f(x)*sin(M_PI*i*x/P);};
      a.emplace_back(integral(-P, P, af, 10*n) / P);
      b.emplace_back(integral(-P, P, bf, 10*n) / P);
    }
  }

  double res = a[0] / 2.0;

  for (int i = 1; i < n; i++)
  {
    res += a[i]*cos(M_PI*i*x/P) + b[i]*sin(M_PI*i*x/P);
  }
  return res;
}