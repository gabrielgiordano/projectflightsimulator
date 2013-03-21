#include "../headers/flight.h"
#include <iostream>
using namespace std;

#define W 87
#define w 119
#define A 65
#define a 97
#define S 83
#define s 115
#define D 68
#define d 100

Flight::Flight() 
{
    eye.x = 1.0;
    eye.y = 1.0;
    eye.z = 1.0;
    look.x = 1.0;
    look.y = 0.0;
    look.z = 1.0;
    upp.x = 2.0;
    upp.y = 2.0;
    upp.z = 2.0;
}
void Flight::display ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.00, 0.745, 0.494);
    glBegin(GL_QUADS);
        glVertex3f( 1.0, 0.0,  1.0);
        glVertex3f( 1.0, 0.0, -1.0);
        glVertex3f(-1.0, 0.0, -1.0);
        glVertex3f(-1.0, 0.0,  1.0);
    glEnd();
    glutSwapBuffers();
}

void Flight::reshape(GLint width, GLint height){
    glViewport(0, 0, (GLsizei) width, (GLsizei) height); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluPerspective(viewAngle, aspectRatio, N, F);
    gluPerspective(60.0, (GLfloat) width / (GLfloat) height, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y,  eye.z,        // coordenadas do observador 
                look.x, look.y, look.z,      // “ponto de interesse” 
                upp.x,  upp.y,  upp.z);      //  direção do vetor view up
}

void Flight::keyboard(GLubyte key, GLsizei x, GLsizei y) {
    switch(key) {
        case W:
        case w:
            cout << "w\n";
            break;
        case A:
        case a:
            cout << "a\n";
            break;
        case S:
        case s:
            cout << "s\n";  
            break;
        case D:
        case d:
            cout << "d\n";
            break;
    }
}

void Flight::mouse(GLsizei button, GLsizei state, GLsizei x, GLsizei y)
{
    // if (button == GLUT_RIGHT_BUTTON) {
    //     if (state == GLUT_DOWN){
    //         createMenu();
    //     }
    // }
}

void Flight::load() 
{
    glClearColor(0.706, 0.851, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
}