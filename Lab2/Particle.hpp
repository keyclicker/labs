#pragma once
#include "Vector.hpp"
#include <cmath>

class Particle
{
public:
  float radius;
  Vector pos;
  Vector vel;

  Particle() = default;
  //Particle(const Particle &val) = default;
  //Particle &operator=(const Particle & val) = default;

  Particle(const float radius, const Vector &pos, const Vector &vel = Vector()) :
    radius(radius), pos(pos), vel(vel) {}

  void move(const Vector &d)
  {
    pos = pos + d;
  }
  void applyForce(const Vector &force, const float time)
  {
    vel = vel + force * time;
  }
  void iter(const float time)
  {
    pos = pos + vel * time;
  }
  friend float dist(const Particle &a, const Particle &b)
  {
    return dist(a.pos, b.pos);
  }
};

