#pragma once

#include <functional>
#include <limits>
#include <vector>

class Shape {
private:
  using FunType = std::function<double(double)>;
  static constexpr double DefaultStep = 0.000001;

  FunType upper, lower;

public:
  explicit Shape(FunType upper = [](auto x){return 0;},
        FunType lower = [](auto x){return 0;}):
        upper(std::move(upper)), lower(std::move(lower)) {}

  double getArea(double sp, double ep, double step = DefaultStep) {
    double area = 0;
    for (double i = sp; i < ep; i += step) {
      area += (step * (upper(i) - lower(i) +
                       upper(i+ step) - lower(i+ step))) / 2.0;
    }
    return area;
  }

  double getPerimeter(double sp, double ep, double step = DefaultStep) {
    double perim = abs(upper(sp) - lower(sp)) + abs(upper(ep) - lower(ep));
    for (double i = sp; i < ep; i += step) {
      perim += hypot(upper(i+ step) - upper(i), step) +
               hypot(lower(i+ step) - lower(i), step);
    }
    return perim;
  }
};