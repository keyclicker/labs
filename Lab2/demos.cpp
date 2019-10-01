#include "demos.hpp"
#include "config.hpp"

extern std::mt19937 rng;

std::uniform_real_distribution
        randDir(-1.0, 1.0);

std::uniform_int_distribution
        randW(-w/16,w/16),
        randH(-h/16,h/16);

void billiard(Space &space)
{
  space.reserve(16);

  space.push(10, 0, 0);

  space.push(10, 18,-10);
  space.push(10, 18, 10);

  space.push(10, 36,-20);
  space.push(10, 36, 0);
  space.push(10, 36, 20);

  space.push(10, 54,-30);
  space.push(10, 54,-10);
  space.push(10, 54,10);
  space.push(10, 54,30);

  space.push(10, 72,-40);
  space.push(10, 72,-20);
  space.push(10, 72, 0);
  space.push(10, 72, 20);
  space.push(10, 72, 40);

  space.push(10, -500, 0, 1000, 0);
}

void genSpace(Space &space, unsigned int count, double radius)
{
  space.reserve(count);

  for (int i = 0; i < count; ++i)
  {
    double px = randW(rng);
    double py = randH(rng);

    double vx = 100.0 * randDir(rng);
    double vy = 100.0 * randDir(rng);

    space.push(radius, px, py, vx, vy);
  }
}