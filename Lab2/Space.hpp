#pragma once

#include "Particle.hpp"
#include <vector>

class Space
{
private:
  double w = 2, h = 2;
  double entropy = 5000;
  double speed = 0.5;
  double resistance = 0.998;
  std::vector<Particle> particles;

  void collisionDetection();

public:
  Space() = default;
  Space(const Space &val) = delete;
  Space &operator=(const Space &val) = delete;

  void push(const Particle &val);
  void push(size_t r, double px, double py, double vx = 0.0, double vy = 0.0);
  void reserve(size_t val);

  void step(double time = 0.1);

  const std::vector<Particle> &getPars();
  void setEntropy(double entropy);
  void setSpeed(double speed);
  void setResistance(double resistance);
};