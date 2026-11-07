#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Vector
{
private:
  vector<double> arr;

public:
  Vector() = default;
  explicit Vector(int size) : arr(size) {};

  void resize(int size)
  {
    arr.resize(size);
  }

  size_t size()
  {
    return arr.size();
  }

  double &operator[](size_t n)
  {
    return arr[n];
  }

  double norm()
  {
    double sum = 0;
    for (int i = 0; i < this->size(); ++i)
    {
      sum += (*this)[i] * (*this)[i];
    }
    return sqrt(sum);
  }

  friend ostream &operator<< (ostream &out, const Vector &val)
  {
    out << "{";
    for (auto i = val.arr.begin(); i != val.arr.end()-1; ++i)
    {
      out << *i << ", ";
    }
    out << val.arr.back() << "};";

    return out;
  }

  friend istream &operator>> (istream &in, Vector &val)
  {
    for (auto &a : val.arr)
    {
      in >> a;
    }

    return in;
  }

  Vector operator+(Vector &val)
  {
    if (val.size() != this->size()) throw logic_error("Vectors have different size!");

    Vector res(this->size());
    for (size_t i = 0; i < this->size(); ++i)
    {
      res[i] = (*this)[i] + val[i];
    }
    return res;
  }

  Vector operator-(Vector &val)
  {
    if (val.size() != this->size()) throw logic_error("Vectors have different size!");

    Vector res(this->size());
    for (size_t i = 0; i < this->size(); ++i)
    {
      res[i] = (*this)[i] - val[i];
    }
    return res;
  }

  double operator*(Vector &val)
  {
    if (val.size() != this->size()) throw logic_error("Vectors have different size!");

    double res = 0;
    for (size_t i = 0; i < this->size(); ++i)
    {
      res += (*this)[i] * val[i];
    }
    return res;
  }
};


int main()
{
  int n;
  cin >> n;

  Vector a(n), b(n);
  cin >> a >> b;

  cout << "a = " << a << " b = " << b << endl;
  cout << "||a|| = " << a.norm() << " ||b|| = " << b.norm() << endl;

  cout << "a + b = " << a + b << endl;
  cout << "a - b = " << a - b << endl;
  cout << "a * b = " << a * b << endl;

}