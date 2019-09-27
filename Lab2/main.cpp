#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "Space.hpp"
#include "Particle.hpp"

using namespace std;

constexpr float pi = M_PI;

constexpr int w = 1920;
constexpr int h = 1080;

Space space;


//all values in pixels
void drawCircle(const float xv, const float yv, const float radius)
{
  constexpr int pofig = 100;

  glBegin(GL_POLYGON);

  for (int i = 0; i < pofig; ++i)
  {
    float x = 2.0*(xv + radius * sin(2.0 * pi * i / pofig))/w;
    float y = 2.0*(yv + radius * cos(2.0 * pi * i / pofig))/h;
    glVertex2f(x, y);
  }

  // glColor3f( 1, 0, 0 ); // red
  //  glVertex2f( -0.8, -0.8 );

  glEnd();
}

void update()
{
  space.iter(0.0002);
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
  space.genSpace(500, 10);

 // space.pushParticle(Particle(100, Vector(0,0), Vector(100, 0)));
 // space.pushParticle(Particle(200, Vector(1000,0), Vector(-100, 0)));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);    // Use single color buffer and no depth buffer.
  glutInitWindowSize(1920, 1080);         // Size of display area, in pixels.
  glutInitWindowPosition(100, 100);     // Location of window in screen coordinates.
  glutCreateWindow("Particle move");// Parameter is window title.
//  glutFullScreen();
  glutDisplayFunc(display);            // Called when the window needs to be redrawn.
  glutIdleFunc(update);

  glutMainLoop(); // Run the event loop!  This function does not return.
  // Program ends when user closes the window.
  return 0;

}