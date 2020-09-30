#include "Space.hpp"
#include "Particle.hpp"
#include "config.hpp"
#include <random>

std::random_device rd;
std::mt19937 rng(rd());

extern std::uniform_real_distribution randDir;

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

  if (sideCollision)
  {
    for (auto &a : particles)
    {
      if (a.pos.x - a.radius < -::w / 2.0)
        a.vel.x = -a.vel.x;
      if (a.pos.x + a.radius > ::w / 2.0)
        a.vel.x = -a.vel.x;
      if (a.pos.y - a.radius < -::h / 2.0)
        a.vel.y = -a.vel.y;
      if (a.pos.y + a.radius > ::h / 2.0)
        a.vel.y = -a.vel.y;
    }
  }
}

void Space::step(const double time)
{
  for (auto &a : particles)
  {
    double dx = entropy * randDir(rng);
    double dy = entropy * randDir(rng);

    a.vel = a.vel * resistance;
    a.applyForce(Vector(dx, dy), time * speed);
    a.step(time * speed);
  }
  collisionDetection();
}

void Space::push(const Particle &val)
{
  particles.emplace_back(val);
}

void Space::push(size_t r, double px, double py, double vx, double vy)
{
  particles.emplace_back(Particle(r, Vector(px, py), Vector(vx, vy)));
}

void Space::reserve(size_t val)
{
  particles.reserve(val);
}

const std::vector<Particle> &Space::getPars()
{
  return particles;
}

void Space::setEntropy(double entropy)
{
  this->entropy = entropy;
}

void Space::setSpeed(double speed)
{
  this->speed = speed;
}

void Space::setResistance(double resistance)
{
  this->resistance = resistance;
}
