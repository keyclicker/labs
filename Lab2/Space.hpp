#pragma once

#include "Particle.hpp"
#include <vector>

class Space
{
private:
  double w = 2, h = 2;
  std::vector<Particle> particles;

  void collisionDetection();

public:
  Space() = default;
  Space(const Space &val) = delete;
  Space &operator=(const Space &val) = delete;

  void push(const Particle &val);
  void push(size_t r, double px, double py, double vx = 0.0, double vy = 0.0);
  void reserve(size_t val);

  void genSpace(unsigned int count, double radius);

  void iter(double time = 0.1);

  const std::vector<Particle> &getPars();

};