#pragma once

class Vector
{
public:
  float x, y;

  Vector() = default;
  Vector(const Vector &val) = default;
  Vector &operator=(const Vector &val) = default;

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
};

class Particle
{
public:
  float radius;
  Vector position;
  Vector velocity;

  Particle() = default;
  Particle(const Particle &val) = default;
  Particle &operator=(const Particle & val) = default;

  Particle(float radius, Vector pos, Vector vel = Vector()) :
    radius(radius), position(pos), velocity(vel) {}


  void move(const Vector &d)
  {
    position = position + d;
  }
  void applyForce(const Vector &force, const float time)
  {
    velocity = velocity + force * Vector(time, time); //not the best decision
  }
  void iter(const float time)
  {
    position = position + velocity * Vector(time, time); //not the best as well
  }
};

