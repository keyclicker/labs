#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

sf::Color HSV(float H, float S, float V) {
  H = std::fmod(H, 360);
  S = clip(S, 0.f, 100.f);
  V = clip(V, 0.f, 100.f);

  float s = S / 100;
  float v = V / 100;
  float C = s * v;
  float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
  float m = v - C;
  float r, g, b;

  if (H >= 0 && H < 60) {
    r = C, g = X, b = 0;
  } else if (H >= 60 && H < 120) {
    r = X, g = C, b = 0;
  } else if (H >= 120 && H < 180) {
    r = 0, g = C, b = X;
  } else if (H >= 180 && H < 240) {
    r = 0, g = X, b = C;
  } else if (H >= 240 && H < 300) {
    r = X, g = 0, b = C;
  } else {
    r = C, g = 0, b = X;
  }

  int R = (r + m) * 255;
  int G = (g + m) * 255;
  int B = (b + m) * 255;

  return sf::Color(R, G, B);
}