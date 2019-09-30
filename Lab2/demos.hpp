#pragma once
#include "Space.hpp"

void billiard(Space &space)
{
  space.pushParticle(Particle(10, Vector(0,0)));

  space.pushParticle(Particle(10, Vector(18,-10)));
  space.pushParticle(Particle(10, Vector(18,10)));

  space.pushParticle(Particle(10, Vector(36,-20)));
  space.pushParticle(Particle(10, Vector(36,0)));
  space.pushParticle(Particle(10, Vector(36,20)));

  space.pushParticle(Particle(10, Vector(54,-30)));
  space.pushParticle(Particle(10, Vector(54,-10)));
  space.pushParticle(Particle(10, Vector(54,10)));
  space.pushParticle(Particle(10, Vector(54,30)));

  space.pushParticle(Particle(10, Vector(72,-40)));
  space.pushParticle(Particle(10, Vector(72,-20)));
  space.pushParticle(Particle(10, Vector(72,0)));
  space.pushParticle(Particle(10, Vector(72,20)));
  space.pushParticle(Particle(10, Vector(72,40)));

  space.pushParticle(Particle(10, Vector(-500,0), Vector(1000, 0)));
}