#pragma once
#include <cmath>

class Vector
{
public:
  float x, y;

  Vector() = default;
  //Vector(const Vector &val) = default;
  //Vector &operator=(const Vector &val) = default;

  Vector(float x, float y) : x(x), y(y) {}

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

  friend Vector operator*(const float a, const Vector &b)
  {
    return Vector(a * b.x, a * b.y);
  }
  friend Vector operator*(const Vector &a, const float b)
  {
    return Vector(a.x * b, a.y * b);
  }
  friend Vector operator/(const float a, const Vector &b)
  {
    return Vector(a / b.x, a / b.y);
  }
  friend Vector operator/(const Vector &a, const float b)
  {
    return Vector(a.x / b, a.y / b);
  }

  float len() const
  {
    return std::hypot(x, y);
  }

  friend float dist(const Vector &a, const Vector &b)
  {
    return hypot(a.x-b.x, a.y-b.y);
  }
};