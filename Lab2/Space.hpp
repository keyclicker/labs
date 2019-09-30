#pragma once

#include "Particle.hpp"
#include <vector>

class Space
{
private:
  double w = 2, h = 2;
  std::vector<Particle> particles;

  void colisionDetection();

public:
  Space() = default;
  Space(const Space &val) = delete;
  Space &operator=(const Space &val) = delete;

  void pushParticle(const Particle &val);
  void genSpace(const unsigned int count, const double radius);

  void iter(double time = 0.1);

  const std::vector<Particle> &getPars();

};