#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <chrono>

#include "Space.hpp"
#include "config.hpp"
#include "demos.hpp"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace std::chrono;




int main()
{
    sf::RenderWindow window(sf::VideoMode(w, h), "Lab1");
    sf::Clock clock;

    float cx = 0, cy = 0; //camera x, y
    float cz = 1; //camera zoom

    Space space = billiard();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        double e = 0;
        for (auto &a : space.getPars())
        {
            sf::CircleShape shape(100.f);
            shape.setFillColor(sf::Color::Green);

            double k = 100.0 / a.vel.len();

            if(isColored)
                shape.setFillColor(sf::Color(255.0 / k, 0, min(255.0 * k, 255.0)));
            else
                shape.setFillColor(sf::Color(0, k*0.80, k*0.20));

            shape.setPosition(a.pos.x + w / 2.0, -a.pos.y + h / 2.0);
            shape.setRadius(a.radius);
            window.draw(shape);

            e += a.vel.len() * a.vel.len();
        }

        window.display();

        space.step(clock.getElapsedTime().asSeconds());
    }

    return 0;
}
