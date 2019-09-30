#include "Space.hpp"
#include "Particle.hpp"
#include "config.hpp"
#include <random>

std::random_device rd;
std::mt19937 rng(rd());

std::uniform_int_distribution
randW(-w/16,w/16),
randH(-h/16,h/16);

std::uniform_real_distribution
randDir(-1.0, 1.0);

void Space::collisionDetection()
{
  for (auto a = particles.begin(); a != particles.end(); ++a)
  {
    for (auto b = a; b != particles.end(); ++b)
    {
      if (dist(*a, *b) <= a->radius + b->radius && a != b)
      {
        Vector pv = Vector(b->pos - a->pos); //projection vector

        double adt = a->vel.x * pv.x + a->vel.y * pv.y; //Dot product
        double ascl = adt / pv.len(); //scalar projection

        double bdt = b->vel.x * pv.x + b->vel.y * pv.y; //Dot product
        double bscl = bdt / pv.len(); //scalar projection

        Vector baseVec = pv / pv.len(); // a to b vector with length = 1

        Vector aprj = ascl * baseVec; //vector projection
        Vector bprj = -bscl * baseVec; //vector projection

        //Momentum conservation vector
        Vector mcVec = (ascl - bscl)  * baseVec;

        a->vel = a->vel - mcVec;
        b->vel = b->vel + mcVec;

        //collision antiglitch
        double d = ((a->radius + b->radius) - dist(*a, *b)) / 2.0;

        a->pos = a->pos - d * baseVec;
        b->pos = b->pos + d * baseVec;
      }
    }
  }

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
}

void Space::iter(const double time)
{
  for (auto &a : particles)
  {
    double dx = cEntropy * randDir(rng);
    double dy = cEntropy * randDir(rng);

    a.vel = a.vel * cResistance;
    a.applyForce(Vector(dx, dy), time * cSpeed);
    a.iter(time * cSpeed);
  }
  collisionDetection();
}

void Space::pushParticle(const Particle &val)
{
  particles.emplace_back(val);
}

void Space::genSpace(const unsigned int count, const double radius)
{
  particles.reserve(count);

  for (int i = 0; i < count; ++i)
  {
    double x, y;

    x = randW(rng);
    y = randH(rng);

    double xv = 100.0 * randDir(rng);
    double yv = 100.0 * randDir(rng);
    particles.emplace_back(radius, Vector(x, y), Vector(xv, yv));
  }
}

const std::vector<Particle> &Space::getPars()
{
  return particles;
}