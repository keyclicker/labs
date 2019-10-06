#include "GraphBuilder.hpp"
#include <cmath>

void GraphBuilder::run()
{
  sf::RenderWindow window(sf::VideoMode(w, h), "Grapgh Builder");
  glEnable(GL_TEXTURE_2D);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto f : functions)
      draw(f);

    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
      zoom *= cZoomSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
      zoom /= cZoomSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      dy -= cMoveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      dy += cMoveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      dx += cMoveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      dx -= cMoveSpeed;
    }

  }
}

void GraphBuilder::draw(const Function &f)
{
  //aspect ratio
  auto ar = (double) w / h;

  glColor3f(0.5, 0.5, 0.5);
  glBegin(GL_LINES);

  glVertex2d(-1, dy);
  glVertex2d(1, dy);

  glVertex2d(dx, -1);
  glVertex2d(dx, 1);

  glEnd();

  glColor3f(0, 1, 0.2);
  glBegin(GL_LINE_STRIP);

  for (double x = -1; x < 1; x += 2.0 / w)
  {
    glVertex2d(x, f((x-dx)/zoom*ar)*zoom + dy);
  }

  glEnd();
}

void GraphBuilder::addFunc(const Function &f)
{
  functions.push_back(f);
}
