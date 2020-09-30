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
  /// Constructor
  /// @param upper Upper function
  /// @param lower Lower function
  explicit Shape(FunType upper = [](auto x){return 0;},
        FunType lower = [](auto x){return 0;}):
        upper(std::move(upper)), lower(std::move(lower)) {}

  /// Upper function setter
  /// @param upper Upper function
  template<typename Func>
  void setUpper(Func &&upper) {
    Shape::upper = std::forward<Func>(upper);
  }

  /// Lower function setter
  /// @param lower Lower function
  template<typename Func>
  void setLower(Func &&lower) {
    Shape::lower = std::forward<Func>(lower);
  }

  /// Calculating area function
  /// @param sp Starting point
  /// @param ep Ending point
  /// @param step Step that sets precision of calculation
  /// @return Calculated area
  double getArea(double sp, double ep, double step = DefaultStep) const {
    double area = 0;
    for (double i = sp; i < ep; i += step) {
      area += (step * (upper(i) - lower(i) +
                       upper(i + step) - lower(i+ step))) / 2.0;
    }
    return area;
  }

  /// Calculating perimeter function
  /// @param sp Starting point
  /// @param ep Ending point
  /// @param step Step that sets precision of calculation
  /// @return Calculated precision
  double getPerimeter(double sp, double ep, double step = DefaultStep) const {
    double perim = abs(upper(sp) - lower(sp)) + abs(upper(ep) - lower(ep));
    for (double i = sp; i < ep; i += step) {
      perim += hypot(upper(i + step) - upper(i), step) +
               hypot(lower(i + step) - lower(i), step);
    }
    return perim;
  }

  friend double intersectionArea(Shape &s1, Shape &s2, double sp, double ep, double step);

  friend double unionArea(Shape &s1, Shape &s2, double sp, double ep, double step);
};

double intersectionArea(Shape &s1, Shape &s2,
                        double sp, double ep,
                        double step = Shape::DefaultStep) {
  double area = 0;
  for (double i = sp; i < ep; i += step) {
    area += (step * (std::min(s1.upper(i), s2.upper(i)) -
                     std::max(s1.lower(i), s2.lower(i)) +
                     std::min(s1.upper(i + step), s2.upper(i + step)) -
                     std::max(s1.lower(i + step), s2.lower(i + step)))) / 2.0;
  }
  return area;
}

double unionArea(Shape &s1, Shape &s2,
                 double sp, double ep,
                 double step = Shape::DefaultStep) {
  double area = 0;
  for (double i = sp; i < ep; i += step) {
    area += (step * (std::max(s1.upper(i), s2.upper(i)) -
                     std::min(s1.lower(i), s2.lower(i)) +
                     std::max(s1.upper(i + step), s2.upper(i + step)) -
                     std::min(s1.lower(i + step), s2.lower(i + step)))) / 2.0;
  }
  return area;
}
