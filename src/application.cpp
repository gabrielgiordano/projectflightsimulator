#include "../headers/application.h"

#define LEFT_ARROW 100
#define UP_ARROW 101
#define RIGHT_ARROW 102
#define DOWN_ARROW 103
#define ESC 27
#define W 87
#define w 119
#define A 65
#define a 97
#define S 83
#define s 115
#define D 68
#define d 100
#define l 108
#define L 76


Application::Application()
{
    lightAmbient = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    lightDiffuse = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    lightPosition = vec4(0.0f, 0.0f, 5.0f, 1.0f);
}

void Application::display ()
{
    // Clear The Screen And The Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset The Current Modelview Matrix
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, 0.0f);

    object.draw();

    glutSwapBuffers();
}

void Application::reshape(GLint width, GLint height) 
{
    // Prevent A Divide By Zero By
    if (height == 0)
        height = 1; // Making Height Equal One
 
    glViewport(0, 0, width, height);

    // Select The Projection Matrix
    glMatrixMode(GL_PROJECTION);
    // Reset The Projection Matrix
    glLoadIdentity();
 
    // Calculate The Aspect Ratio Of The Window
    gluPerspective(60.0f,(GLdouble)width/(GLdouble)height,0.1f,300.0f);

    // Select The Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Application::keyboard(GLubyte key, GLsizei x, GLsizei y) {
    switch(key) {
        case W:
        case w:
            object.translate(vec3(0.0f, 0.0f, -1.0f));
            break;
        case A:
        case a:
            break;
        case S:
        case s:
            object.translate(vec3(0.0f, 0.0f, +1.0f));
            break;
        case D:
        case d:
            break;
        default:
        ;
    }
}

void Application::special(GLint key, GLint x, GLint y) { 
    switch(key) {
        case UP_ARROW:
            object.rotateInAxisX(-1.0f);
            break;
        case DOWN_ARROW:
            object.rotateInAxisX(+1.0f);
            break;
        case LEFT_ARROW:
            object.rotateInAxisZ(-1.0f);
            break;
        case RIGHT_ARROW:
            object.rotateInAxisZ(+1.0f);  
            break;
    }
}

void Application::load() 
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel (GL_SMOOTH);
    // glClearColor(0.706, 0.851, 1.0, 0.0);    
    glClearColor(0.0, 0.0, 0.0, 0.0);    
    // Depth Buffer Setup
    glClearDepth(1.0f);
    // Enables Depth Testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // Really Nice Perspective Calculations
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    startEnvironment();

    // Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_AMBIENT, &lightAmbient[0]);
    // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, &lightDiffuse[0]);
    // Position The Light
    glLightfv(GL_LIGHT1, GL_POSITION, &lightPosition[0]);
    // Enable Light One
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
}

void Application::startEnvironment() 
{
    object.loadTexture("textures/tower.jpg");
    object.loadOBJ("models/tower.obj");
}