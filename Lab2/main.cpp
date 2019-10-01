#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <chrono>

#include "Space.hpp"
#include "config.hpp"
#include "demos.hpp"

using namespace std;
using namespace std::chrono;

Space space;

//all values in pixels
void drawCircle(const double xv, const double yv, const double radius)
{
  constexpr int detail = 100;

  glBegin(GL_POLYGON);

  for (int i = 0; i < detail; ++i)
  {
    double x = 2.0*(xv + radius * sin(2.0 * pi * i / detail))/w;
    double y = 2.0*(yv + radius * cos(2.0 * pi * i / detail))/h;
    glVertex2f(x, y);
  }

  // glColor3f( 1, 0, 0 ); // red
  //  glVertex2f( -0.8, -0.8 );

  glEnd();
}

static high_resolution_clock::time_point
oldT, newT = high_resolution_clock::now();

void update()
{
  oldT = newT;
  newT = high_resolution_clock::now();

  duration<double> time_span = duration_cast<duration<double>>(newT - oldT);
  space.iter(time_span.count());
  cout << 1.0/time_span.count() << endl;

  glutPostRedisplay();
}

void display()
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  double e = 0;
  for (auto &a : space.getPars())
  {
    double k = 100.0 / a.vel.len();
    glColor3f(1.0/k, 0, k);
    drawCircle(a.pos.x, a.pos.y, a.radius);
    e += a.vel.len() * a.vel.len();
  }
  //std::cout << e << std::endl;

  glutSwapBuffers();
}

int main(int argc, char **argv)
{
  genSpace(space, 400, 3);
// billiard(space);

  //space.push(100, 0, 0, 0, 0);
  //space.push(100, 500, 0, -1000, 0);


  glutInit(&argc, argv);
  glutSetOption(GLUT_MULTISAMPLE, 4);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutInitWindowSize(w, h);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Particle move");
  //glutFullScreen();
  glutDisplayFunc(display);
  glutIdleFunc(update);

  glutMainLoop();
  return 0;
}