#pragma once
#include <cmath>

class Vector
{
public:
  double x, y;

  Vector() = default;

  Vector(double x, double y) : x(x), y(y) {}

  Vector operator+(const Vector &val) const
  {
    return Vector(x + val.x, y + val.y);
  }
  Vector operator-(const Vector &val) const
  {
    return Vector(x - val.x, y - val.y);
  }
  Vector operator*(const Vector &val) const
  {
    return Vector(x * val.x, y * val.y);
  }
  Vector operator/(const Vector &val) const
  {
    return Vector(x / val.x, y / val.y);
  }

  friend Vector operator*(double a, const Vector &b)
  {
    return Vector(a * b.x, a * b.y);
  }
  friend Vector operator*(const Vector &a, double b)
  {
    return Vector(a.x * b, a.y * b);
  }
  friend Vector operator/(double a, const Vector &b)
  {
    return Vector(a / b.x, a / b.y);
  }
  friend Vector operator/(const Vector &a, double b)
  {
    return Vector(a.x / b, a.y / b);
  }

  double len() const
  {
    return std::hypot(x, y);
  }

  friend double dist(const Vector &a, const Vector &b)
  {
    return hypot(a.x-b.x, a.y-b.y);
  }
};