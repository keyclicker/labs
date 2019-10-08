#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;

//token from https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
sf::Color hsv2rgb(float h, float s, float v)
{
  double hh, p, q, t, ff;
  long i;
  sf::Color out;

  if(s <= 0.0) {       // < is bogus, just shuts up warnings
    out.r = v * 255;
    out.g = v * 255;
    out.b = v * 255;
    return out;
  }
  hh = h;
  if(hh >= 360.0) hh = 0.0;
  hh /= 60.0;
  i = (long)hh;
  ff = hh - i;
  p = v * (1.0 - s);
  q = v * (1.0 - (s * ff));
  t = v * (1.0 - (s * (1.0 - ff)));

  switch(i)
  {
    case 0:
      out.r = v * 255;
      out.g = t * 255;
      out.b = p * 255;
      break;
    case 1:
      out.r = q * 255;
      out.g = v * 255;
      out.b = p * 255;
      break;
    case 2:
      out.r = p * 255;
      out.g = v * 255;
      out.b = t * 255;
      break;

    case 3:
      out.r = p * 255;
      out.g = q * 255;
      out.b = v * 255;
      break;
    case 4:
      out.r = t * 255;
      out.g = p * 255;
      out.b = v * 255;
      break;
    case 5:
    default:
      out.r = v * 255;
      out.g = p * 255;
      out.b = q * 255;
      break;
  }
  return out;
}