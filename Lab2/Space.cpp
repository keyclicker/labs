#include "Space.hpp"
#include "Particle.hpp"
#include <cstdlib>

void Space::colisionDetection()
{
  for (auto &a : particles)
  {
    for (auto &b : particles)
    {
      if (dist(a, b) <= a.radius + b.radius && &a != &b)
      {
        Vector pv = Vector(b.pos - a.pos); //projection vector
        float scl = a.vel.x * pv.x + a.vel.y * pv.y;
        float prj = scl / pv.len();

        Vector vec = 2 * prj * pv / pv.len();
        a.vel = a.vel - vec;
      }
    }
  }

  for (auto &a : particles)
  {
    if (a.pos.x - a.radius < -960)
      a.vel.x = -a.vel.x;
    if (a.pos.x + a.radius > 960)
      a.vel.x = -a.vel.x;
    if (a.pos.y - a.radius < -540)
      a.vel.y = -a.vel.y;
    if (a.pos.y + a.radius > 540)
      a.vel.y = -a.vel.y;
  }

}

void Space::iter(const float time)
{
  for (auto &a : particles)
  {
    float dx = 2 * (float) rand() / RAND_MAX - 1;
    float dy = 2 * (float) rand() / RAND_MAX - 1;
    a.applyForce(Vector(dx, dy), time*10000000);
    a.iter(time);
  }
  colisionDetection();
}

void Space::pushParticle(const Particle &val)
{
  particles.push_back(val);
}

void Space::genSpace(const unsigned int count, const float radius)
{
  for (int i = 0; i < count; ++i)
  {
    float x, y;

    bool k = true;
    while (k)
    {
      x = rand() % 960 - 480; //needs C++11 modification
      y = rand() % 540 - 270;

      k = false;
      for (auto &a : particles)
      {
        if (dist(a.pos, Vector(x, y)) <= 2.0 * radius)
        {
          k = true;
        }
      }
    }

    float xv = rand() % 960 - 480; //needs C++11 modification
    float yv = rand() % 540 - 270;
    particles.emplace_back(radius, Vector(x, y), Vector(xv, yv));
  }
}

const std::list<Particle> &Space::getPars()
{
  return particles;
}