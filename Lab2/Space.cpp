#include "Space.hpp"
#include <cstdlib>

void Space::pushParticle(const Particle &val)
{
  particles.push_back(val);
}

void Space::iter(const float time)
{
  for (auto &a : particles)
  {
    float dx = 2 * (float) rand() / RAND_MAX - 1;
    float dy = 2 * (float) rand() / RAND_MAX - 1;
    a.applyForce(Vector(dx * 2, dy * 2), time);
    a.iter(time);
  }
}

void Space::genSpace(const unsigned int count)
{
  for (int i = 0; i < count; ++i)
  {
    float x = 2 * (float) rand() / RAND_MAX - 1; //needs C++11 modification
    float y = 2 * (float) rand() / RAND_MAX - 1; ///////
    particles.emplace_back(defaultRadius, Vector(x, y));
  }
}

const std::list<Particle> &Space::getPars()
{
  return particles;
}
