#pragma once

#include "Particle.hpp"
#include <vector>

class Space
{
private:
  bool sideCollision = true;
public:
  void setSideCollision(bool sideCollision);

private:
  double entropy = 0;
  double speed = 1;
  double resistance = 1;
  std::vector<Particle> particles;

  void collisionDetection();

public:
  Space() = default;
  Space(const Space &val) = delete;
  Space &operator=(const Space &val) = delete;

  Space(Space &&val) = default;

  void push(const Particle &val);
  void push(size_t r, double px, double py, double vx = 0.0, double vy = 0.0);
  void reserve(size_t val);

  void step(double time = 0.1);

  const std::vector<Particle> &getPars();
  void setEntropy(double entropy);
  void setSpeed(double speed);
  void setResistance(double resistance);
};