#include "FunctionBuilder.hpp"
#include "color.hpp"
#include <cmath>
#include <string>

void FunctionBuilder::run() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(w, h), "Graph Builder",
                          sf::Style::Default, settings);
  window.setFramerateLimit(60);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    glClearColor(0.12, 0.12, 0.12, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);

    for (double x = -1; x < 1; x += 2.0 / w) {
      glVertex2d(x, -0.01);
      glVertex2d(x, 0.01);
    }
    glEnd();

    for (int i = 0; i < functions.size(); ++i) {
      auto c = hsv2rgb(360 * (float) i / functions.size(), 1, 1);
      glColor3f(c.r, c.g, c.b);
      draw(functions[i]);
    }

    window.display();

    auto time = clock.restart().asSeconds();

    static unsigned long long k = 0;
    if (!(k++ % 100))
      window.setTitle(sf::String(std::to_string(1.0 / time)));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
      zoom *= cZoomSpeed * (1 + time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
      zoom /= cZoomSpeed * (1 + time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      dy -= cMoveSpeed * time;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      dy += cMoveSpeed * time;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      dx += cMoveSpeed * time;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      dx -= cMoveSpeed * time;
    }
  }
}

void FunctionBuilder::draw(const Function &f) const {
  //aspect ratio
  auto ar = (double) w / h;

  glLineWidth(3.0);
  glBegin(GL_LINE_STRIP);

  for (double x = -1; x < 1; x += 2.0 / w) {
    glVertex2d(x, f((x - dx) / zoom * ar) * zoom + dy);
  }
  glEnd();

  glColor4f(1, 1, 1, 0.5);
  glLineWidth(1.0);
  glBegin(GL_LINES);

  glVertex2d(-1, dy);
  glVertex2d(1, dy);

  glVertex2d(dx, -1);
  glVertex2d(dx, 1);

  glEnd();

}