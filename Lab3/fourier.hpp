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
double fourier(const Function &f, double x,  int n)
{
  static vector<double> a, b;
  a.reserve(n);
  b.reserve(n);

  if (a.size() < n) //&& b.size() < n
  {
    for (int i = a.size(); i < n; ++i)
    {
      auto af = [f, i] (double x) {return f(x)*cos(i*x);};
      auto bf = [f, i] (double x) {return f(x)*sin(i*x);};
      a.emplace_back(integral(-M_PI, M_PI, af, 10*n) / M_PI);
      b.emplace_back(integral(-M_PI, M_PI, bf, 10*n) / M_PI);
    }
  }

//  for (auto i : a) cout << i << ' ';
//  cout << endl;
//  for (auto i : b) cout << i << ' ';
//  cout << endl;

  double res = a[0] / 2.0;

  for (int i = 1; i < n; i++)
  {
    res += a[i]*cos(i*x) + b[i]*sin(i*x);
  }
  return res;
}