#pragma once
#include "Particle.hpp"
#include <list>

constexpr float defaultRadius = 0.5;

class Space
{
private:
  float w = 2, h = 2;
  std::list<Particle> particles;

public:
  Space() = default;
  Space(const Space &val) = delete;
  Space &operator=(const Space &val) = delete;

  void pushParticle(const Particle &val);
  void genSpace(const unsigned int count);

  void iter(float time = 0.1);

  const std::list<Particle> &getPars();

};