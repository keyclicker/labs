#include "../include/Demos.hpp"
#include "../include/Config.hpp"
#include "../include/Random.hpp"

Space billiard() {
  Space space;

  space.setEntropy(0);
  space.setResistance(0.5);
  space.setSpeed(0.25);

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

  space.push(10, -w/2.0 + 20, 0, 3000, 0);

  return space;
}

Space lonelyParticle() {
  Space space;

  space.setEntropy(10000);
  space.setResistance(0.2);
  space.setSpeed(1);

  space.push(5, 0, 0, 0, 0);

  return space;
}

Space genSpace(unsigned int count, double radius) {
  Space space;

  space.setEntropy(10000);
  space.setResistance(0.2);
  space.setSpeed(1);

  space.reserve(count);

  for (int i = 0; i < count; ++i)
  {
    double px = randX();
    double py = randY();

    double vx = 10.0 * randDir();
    double vy = 10.0 * randDir();

    space.push(radius, px, py, vx, vy);
  }

  return space;
}
