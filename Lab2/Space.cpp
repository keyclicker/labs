#include "Space.hpp"
#include "Particle.hpp"
#include "config.hpp"
#include <random>

std::random_device rd;
std::mt19937 rng(rd());

std::uniform_int_distribution
randW(-w/4,w/4),
randH(-h/4,h/4);

std::uniform_real_distribution
randDir(-1.0, 1.0);

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
/*
  for (auto &a : particles)
  {
    if (a.pos.x - a.radius < -::w/2.0)
      a.vel.x = -a.vel.x;
    if (a.pos.x + a.radius > ::w/2.0)
      a.vel.x = -a.vel.x;
    if (a.pos.y - a.radius < -::h/2.0)
      a.vel.y = -a.vel.y;
    if (a.pos.y + a.radius > ::h/2.0)
      a.vel.y = -a.vel.y;
  }
*/
}

void Space::iter(const float time)
{
  for (auto &a : particles)
  {
    float dx = randDir(rng);
    float dy = randDir(rng);
    //a.applyForce(Vector(dx, dy), time*1000000);
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
      x = randW(rng);
      y = randH(rng);

      k = false;
      for (auto &a : particles)
      {
        if (dist(a.pos, Vector(x, y)) <= 2.0 * radius)
        {
          k = true;
        }
      }
    }

    float xv = 2000.0 * randDir(rng);
    float yv = 2000.0 * randDir(rng);
    particles.emplace_back(radius, Vector(x, y), Vector(xv, yv));
  }
}

const std::list<Particle> &Space::getPars()
{
  return particles;
}