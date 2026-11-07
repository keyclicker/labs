#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL\gl.h>
#include <GL\freeglut.h>   // freeglut.h might be a better alternative, if available.
float arr_init[3][2]={{-1,0},{1,0},{0,1}};
float arr[3][2]={{-1,0},{1,0},{0,1}};
float ang=0;
void display() {  // Display function will draw the image.

    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );

    glBegin(GL_LINE_LOOP);
    glColor3f( 1, 0, 0 ); // red
    glVertex2f(arr[0][0],arr[0][1]);
    glColor3f( 0, 1, 0 ); // green
    glVertex2f(arr[1][0],arr[1][1]);
    glColor3f( 0, 0, 1 ); // blue
    glVertex2f(arr[2][0],arr[2][1]);

    glEnd();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.

}

void run()
{
for (int i=0;i<3;i++)
    {
    arr[i][0]=arr_init[i][0]*cos(ang)+arr_init[i][1]*sin(ang);
    arr[i][1]=-arr_init[i][0]*sin(ang)+arr_init[i][1]*cos(ang);
    }
ang=ang+0.001;
glutPostRedisplay();
}

int main( int argc, char** argv ) {  // Initialize GLUT and

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);    // Use single color buffer and no depth buffer.
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.

    glutIdleFunc(run);
    glutMainLoop(); // Run the event loop!  This function does not return.

    return 0;

}
