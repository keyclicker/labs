#pragma once
#include "Vector.hpp"
#include <cmath>

class Particle
{
public:
  double radius;
  Vector pos;
  Vector vel;

  Particle() = default;
  //Particle(const Particle &val) = default;
  //Particle &operator=(const Particle & val) = default;

  Particle(const double radius, const Vector &pos, const Vector &vel = Vector()):
    radius(radius), pos(pos), vel(vel) {}

  void move(const Vector &d)
  {
    pos = pos + d;
  }
  void applyForce(const Vector &force, const double time)
  {
    vel = vel + force * time;
  }
  void iter(const double time)
  {
    pos = pos + vel * time;
  }
  friend double dist(const Particle &a, const Particle &b)
  {
    return dist(a.pos, b.pos);
  }
};

