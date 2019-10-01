#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <chrono>

#include "Space.hpp"
#include "config.hpp"
#include "demos.hpp"

using namespace std;
using namespace std::chrono;

float cx = 0, cy = 0; //camera x, y
float cz = 1; //camera zoom

Space space;

//all values in pixels
void drawCircle(const double xv, const double yv, const double radius)
{
  constexpr int detail = 15;

  glBegin(GL_POLYGON);

  for (int i = 0; i < detail; ++i)
  {
    double x = 2.0*(xv + radius * sin(2.0 * pi * i / detail))/w;
    double y = 2.0*(yv + radius * cos(2.0 * pi * i / detail))/h;
    glVertex2f(x, y);
  }

  glEnd();
}

static high_resolution_clock::time_point
oldT, newT = high_resolution_clock::now();

void update()
{
  oldT = newT;
  newT = high_resolution_clock::now();

  duration<double> time_span = duration_cast<duration<double>>(newT - oldT);
  space.step(time_span.count());

  glutPostRedisplay();
}

void display()
{
  glClearColor(0, 0, 0, 1);

  if (doRedraw)
    glClear(GL_COLOR_BUFFER_BIT);

  double e = 0;
  for (auto &a : space.getPars())
  {
    double k = 100.0 / a.vel.len();

    if(isColored)
      glColor3f(1.0/k, 0, k);
    else
      glColor3f(k, k, k);

    drawCircle((a.pos.x + cx) * cz, (a.pos.y + cy) * cz, a.radius * cz);
    e += a.vel.len() * a.vel.len();
  }

  glutSwapBuffers();
}

void SpecialKeyHandler(int key, int x, int y)
{
  if (key == GLUT_KEY_RIGHT)
  {
    cx -= moveSpeed;
  }
  if (key == GLUT_KEY_LEFT)
  {
    cx += moveSpeed;
  }
  if (key == GLUT_KEY_UP)
  {
    cy -= moveSpeed;
  }
  if (key == GLUT_KEY_DOWN)
  {
    cy += moveSpeed;
  }
  if (key == GLUT_KEY_CTRL_L)
  {
    cz *= zoomSpeed;
  }
  if (key == GLUT_KEY_ALT_L)
  {
    cz /= zoomSpeed;
  }
}

int main(int argc, char **argv)
{
  genSpace(space, 400, 3);
//  billiard(space);
//  lonelyParticle(space);

  glutInit(&argc, argv);
  glutSetOption(GLUT_MULTISAMPLE, 4);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutInitWindowSize(w, h);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Particle move");
  glutDisplayFunc(display);
  glutIdleFunc(update);
  glutSpecialFunc(SpecialKeyHandler);
  glutMainLoop();
  return 0;
}
