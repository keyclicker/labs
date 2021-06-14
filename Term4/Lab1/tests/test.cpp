#include <gtest/gtest.h>
#include "../include/Vector.hpp"
#include "../include/Particle.hpp"
#include "../include/Space.hpp"

TEST(Vector, OperatorPlus) {
  Vector a(1, 0), b(-5, 5);
  EXPECT_EQ(a + b, Vector(-4, 5));
}
TEST(Vector, OperatorMinus) {
  Vector a(1, 0), b(-5, 5);
  EXPECT_EQ(a - b, Vector(6, -5));
}
TEST(Vector, OperatorMul) {
  Vector a(1, 3), b(-5, 5);
  EXPECT_EQ(a * b, Vector(-5, 15));
}
TEST(Vector, OperatorDiv) {
  Vector a(1, 3), b(-5, 5);
  EXPECT_EQ(a / b, Vector(-1.0/5.0, 3.0/5.0));
}
TEST(Vector, OperatorMulNum) {
  Vector a(1, 3);
  EXPECT_EQ(a * 5, Vector(5, 15));
}
TEST(Vector, OperatorDivNum) {
  Vector a(1, 3);
  EXPECT_EQ(a / 10, Vector(1.0/10.0, 3.0/10.0));
}
TEST(Vector, Len) {
  Vector a(5, 3);
  EXPECT_EQ(a.len(), std::hypot(5, 3));
}
TEST(Vector, Dist) {
  Vector a(1, 3), b(-4, -20);
  EXPECT_EQ(dist(a, b), std::hypot(1+4, 3+20));
}


TEST(Particle, Move) {
  Particle a(5, Vector(5, 2), Vector(-2, -2));
  a.move(Vector(-2, -2));
  EXPECT_EQ(a.pos, Vector(3, 0));
}
TEST(Particle, Step) {
  Particle a(5, Vector(5, 2), Vector(-2, -2));
  a.step(2);
  EXPECT_EQ(a.pos, Vector(1, -2));
}
TEST(Particle, ApplyForce) {
  Particle a(5, Vector(5, 2), Vector(-2, -2));
  a.applyForce(Vector(2, 2), 2);
  a.step(2);
  EXPECT_EQ(a.pos, Vector(9, 6));
}