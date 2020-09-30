#pragma once

#include <functional>
#include <limits>
#include <vector>
#include <cmath>

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
  void setUpper(Func &&upper);

  /// Lower function setter
  /// @param lower Lower function
  template<typename Func>
  void setLower(Func &&lower);

  /// Calculates area function
  /// @param sp Starting point
  /// @param ep Ending point
  /// @param step Step that sets precision of calculation
  /// @return Calculated area
  [[nodiscard]]
  double getArea(double sp, double ep, double step = DefaultStep) const;

  /// Calculates perimeter function
  /// @param sp Starting point
  /// @param ep Ending point
  /// @param step Step that sets precision of calculation
  /// @return Calculated perimeter
  [[nodiscard]]
  double getPerimeter(double sp, double ep, double step = DefaultStep) const;

  /// Calculates intersection area
  /// @param s1 First shape
  /// @param s2 Second shape
  /// @param sp Starting point
  /// @param ep Ending point
  /// @param step Step that sets precision of calculation
  /// @return Calculated intersection area
  friend double intersectionArea(Shape &s1, Shape &s2,
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

  /// Calculates union area
  /// @param s1 First shape
  /// @param s2 Second shape
  /// @param sp Starting point
  /// @param ep Ending point
  /// @param step Step that sets precision of calculation
  /// @return Calculated union area
  friend double unionArea(Shape &s1, Shape &s2,
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

  /// Calculates intersection perimeter
  /// @param s1 First shape
  /// @param s2 Second shape
  /// @param sp Starting point
  /// @param ep Ending point
  /// @param step Step that sets precision of calculation
  /// @return Calculated intersection perimeter
  friend double intersectionPerimeter(Shape &s1, Shape &s2,
                               double sp, double ep,
                               double step = Shape::DefaultStep) {
    double perim = std::abs(std::min(s1.upper(sp), s2.upper(sp)) -
                            std::max(s1.lower(sp), s2.lower(sp))) +
                   std::abs(std::min(s1.upper(ep), s2.upper(ep)) -
                            std::max(s1.lower(ep), s2.lower(ep)));

    for (double i = sp; i < ep; i += step) {
      perim += hypot(std::min(s1.upper(i + step), s2.upper(i + step)) -
                     std::min(s1.upper(i), s2.upper(i)), step) +
               hypot(std::max(s1.lower(i + step), s2.lower(i + step)) -
                     std::max(s1.lower(i), s2.lower(i)), step);
    }
    return perim;
  }

  /// Calculates union perimeter
  /// @param s1 First shape
  /// @param s2 Second shape
  /// @param sp Starting point
  /// @param ep Ending point
  /// @param step Step that sets precision of calculation
  /// @return Calculated union perimeter
  friend double unionPerimeter(Shape &s1, Shape &s2,
                        double sp, double ep,
                        double step = Shape::DefaultStep) {
    double perim = std::abs(std::max(s1.upper(sp), s2.upper(sp)) -
                            std::min(s1.lower(sp), s2.lower(sp))) +
                   std::abs(std::max(s1.upper(ep), s2.upper(ep)) -
                            std::min(s1.lower(ep), s2.lower(ep)));

    for (double i = sp; i < ep; i += step) {
      perim += hypot(std::max(s1.upper(i + step), s2.upper(i + step)) -
                     std::max(s1.upper(i), s2.upper(i)), step) +
               hypot(std::min(s1.lower(i + step), s2.lower(i + step)) -
                     std::min(s1.lower(i), s2.lower(i)), step);
    }
    return perim;
  }
};





