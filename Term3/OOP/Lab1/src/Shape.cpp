#include "Shape.hpp"

template<typename Func>
void Shape::setUpper(Func &&upper) {
  Shape::upper = std::forward<Func>(upper);
}

template<typename Func>
void Shape::setLower(Func &&lower)  {
  Shape::lower = std::forward<Func>(lower);
}

double Shape::getArea(double sp, double ep, double step) const {
  double area = 0;
  for (double i = sp; i < ep; i += step) {
    area += (step * (upper(i) - lower(i) +
                     upper(i + step) - lower(i+ step))) / 2.0;
  }
  return area;
}

double Shape::getPerimeter(double sp, double ep, double step) const  {
  double perim = std::abs(upper(sp) - lower(sp)) +
                 std::abs(upper(ep) - lower(ep));
  for (double i = sp; i < ep; i += step) {
    perim += std::hypot(upper(i + step) - upper(i), step) +
             std::hypot(lower(i + step) - lower(i), step);
  }
  return perim;
}