#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <chrono>

#include "../include/Space.hpp"
#include "../include/Config.hpp"
#include "../include/Demos.hpp"
#include "../include/HSV.hpp"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace std::chrono;


int main() {
  sf::RenderWindow window(sf::VideoMode(w, h), "Lab1");
  sf::Clock clock;

  double cx = 0, cy = 0; //camera x, y
  double cz = 1; //camera zoom

  Space space = billiard();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (doRedraw)
      window.clear();

    double e = 0;
    for (auto &a : space.getPars()) {
      sf::CircleShape shape(100.f);
      shape.setFillColor(sf::Color::Green);



      if (isColored)
        shape.setFillColor(HSV(a.vel.len() + 220, 90, 90));
      else
        shape.setFillColor(HSV(0, 0.75, 1));

      shape.setPosition(a.pos.x / cz + w / 2.0 - a.radius - cx,
                        -a.pos.y / cz + h / 2.0 - a.radius - cy);

      shape.setRadius(a.radius / cz);
      window.draw(shape);

      e += a.vel.len() * a.vel.len();
    }


    window.display();

    auto t = clock.restart().asSeconds();
    space.step(t);

    auto ms = t * moveSpeed;
    auto zs = pow(zoomSpeed, t);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
      ms *= 4;
      zs = pow(zs, 4);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      cx -= ms;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      cx += ms;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      cy += ms;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      cy -= ms;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
      cz *= zs;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
      cz /= zs;
    }

  }

  return 0;
}
