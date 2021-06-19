#include "../include/Random.hpp"
#include "../include/Config.hpp"
#include <random>


std::random_device rd;
std::mt19937 rng(rd());

double randDir() {
  static std::uniform_real_distribution randDir(-1.0, 1.0);
  return randDir(rng);
}

double randX() {
  static std::uniform_real_distribution randX(-w/16.0,w/16.0);
  return randX(rng);
}

double randY() {
  static std::uniform_real_distribution randY(-h/16.0,h/16.0);
  return randY(rng);
}

