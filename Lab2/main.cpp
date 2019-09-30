#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "Space.hpp"
#include "Particle.hpp"
#include "config.hpp"

using namespace std;

Space space;


//all values in pixels
void drawCircle(const float xv, const float yv, const float radius)
{
  constexpr int detail = 10;

  glBegin(GL_POLYGON);

  for (int i = 0; i < detail; ++i)
  {
    float x = 2.0*(xv + radius * sin(2.0 * pi * i / detail))/w;
    float y = 2.0*(yv + radius * cos(2.0 * pi * i / detail))/h;
    glVertex2f(x, y);
  }

  // glColor3f( 1, 0, 0 ); // red
  //  glVertex2f( -0.8, -0.8 );

  glEnd();
}

void update()
{
  space.iter(0.0006);
  glutPostRedisplay();
}

void display()
{
  glClearColor(0, 0, 0, 1);  // (In fact, this is the default.)
  glClear(GL_COLOR_BUFFER_BIT);

  double e = 0;
  for (auto &a : space.getPars())
  {
    drawCircle(a.pos.x, a.pos.y, a.radius);
    e += a.vel.len() * a.vel.len();
  }
  std::cout << e << std::endl;

  glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


int main(int argc, char **argv)
{
  //space.genSpace(400, 3);

  space.pushParticle(Particle(100, Vector(0,0), Vector(0, 0)));
  space.pushParticle(Particle(100, Vector(500,0), Vector(-1000, 0)));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(w, h);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Particle move");
  //glutFullScreen();
  glutDisplayFunc(display);
  glutIdleFunc(update);

  glutMainLoop();
  return 0;
}