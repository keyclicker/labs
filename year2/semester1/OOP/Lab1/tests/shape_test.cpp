#include <list>
#include <cmath>
#include <gtest/gtest.h>
#include "../src/Shape.hpp"


TEST(Shape, SqArea) {
  auto s = Shape(
          [](auto x){return 1;},
          [](auto x){return -1;});

  EXPECT_FLOAT_EQ(s.getArea(-1, 1), 4);
}

TEST(Shape, CosArea) {
  auto s = Shape(
          [](auto x){return cos(x);},
          [](auto x){return -cos(x);});

  EXPECT_FLOAT_EQ(s.getArea(-M_PI_2, M_PI_2), 4);
}


TEST(Shape, SqPerimeter) {
  auto s = Shape(
          [](auto x){return 1;},
          [](auto x){return -1;});

  EXPECT_FLOAT_EQ(s.getPerimeter(-1, 1), 8);
}

TEST(Shape, CosPerimeter) {
  auto s = Shape(
          [](auto x){return cos(x);},
          [](auto x){return -cos(x);});

  EXPECT_FLOAT_EQ(s.getPerimeter(-M_PI_2, M_PI_2), 7.6403966);
}

TEST(Shape, IntersectionArea) {
  auto s1 = Shape(
          [](auto x){return x + 1;},
          [](auto x){return -x - 1;});

  auto s2 = Shape(
          [](auto x){return -x + 1;},
          [](auto x){return x - 1;});

  EXPECT_FLOAT_EQ(intersectionArea(s1, s2, -1, 1), 2);
}

TEST(Shape, UnionArea) {
  auto s1 = Shape(
          [](auto x){return x + 1;},
          [](auto x){return -x - 1;});

  auto s2 = Shape(
          [](auto x){return -x + 1;},
          [](auto x){return x - 1;});

  EXPECT_FLOAT_EQ(unionArea(s1, s2, -1, 1), 6);
}