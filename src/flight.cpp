#include "../headers/flight.h"

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


Flight::Flight()
{   
    glm::vec3 eye(0.0f, 0.0f, 0.0f);
    glm::vec3 center(0.0f, 0.0f, -1.0f);
    glm::vec3 upp(0.0f, 1.0f, 0.0f);
    
    observer.initialize(eye, center, upp);

    lightAmbient = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    lightDiffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    lightPosition = glm::vec4(0.0f, 0.0f, 5.0f, 1.0f);
}

void Flight::display ()
{
    // Clear The Screen And The Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset The Current Modelview Matrix
    glLoadIdentity();

    observer.setObserver();
    // glMultMatrixf(&observer.view[0][0]);
    gluLookAt(  5.0f, 5.0f, 5.0f,
                -5.0f, -5.0f, -5.0f,
                0.0f, 1.0f, 0.0f);

    glLineStipple(4, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
        // X AXIS
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);
        // Y AXIS
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);
        // Z AXIS
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();


    vec3 pitch, roll, yaw;
    pitch = observer.axisX - observer.origin;
    yaw = observer.axisY - observer.origin;
    roll = observer.axisZ - observer.origin;

    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        // X AXIS
        //glColor3f(0.871f, 0.376f, 0.376f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3fv(&pitch[0]);
        // Y AXIS
        //glColor3f(0.212f, 0.839f, 0.525f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3fv(&yaw[0]);
        // Z AXIS
        //glColor3f(0.161f, 0.792f, 0.792f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3fv(&roll[0]);
    glEnd();

    glDisable(GL_LINE_STIPPLE);


    glBegin(GL_LINES);
        // X AXIS
        glColor3f(0.871f, 0.376f, 0.376f);
        glVertex3fv(&observer.origin[0]);
        glVertex3fv(&observer.axisX[0]);
        // Y AXIS
        glColor3f(0.212f, 0.839f, 0.525f);
        glVertex3fv(&observer.origin[0]);
        glVertex3fv(&observer.axisY[0]);
        // Z AXIS
        glColor3f(0.161f, 0.792f, 0.792f);
        glVertex3fv(&observer.origin[0]);
        glVertex3fv(&observer.axisZ[0]);
    glEnd();


    /*float Tamanho = 100.0f;
    float piso = -25.0f;
    float teto = 50.0f;
    glBegin(GL_QUADS);
        glColor3f(0.9f, 0.9f, 0.9f);
        glVertex3f(-Tamanho,piso , -Tamanho);
        glVertex3f(-Tamanho, piso,  Tamanho);
        glVertex3f( Tamanho, piso,  Tamanho);
        glVertex3f( Tamanho, piso, -Tamanho);
   
        glVertex3f(-Tamanho, teto, -Tamanho);
        glVertex3f(-Tamanho, teto,  Tamanho);
        glVertex3f( Tamanho, teto,  Tamanho);
        glVertex3f( Tamanho, teto, -Tamanho);
        
        glColor3f(0, 0.9f, 0.9f);    
        glVertex3f(Tamanho, piso, -Tamanho);
        glVertex3f(Tamanho, piso,  Tamanho);
        glVertex3f(Tamanho, teto,  Tamanho);
        glVertex3f(Tamanho, teto, -Tamanho);
   
        //Lado de tras
        glVertex3f(-Tamanho, piso, -Tamanho);
        glVertex3f(-Tamanho, piso,  Tamanho);
        glVertex3f(-Tamanho, teto,  Tamanho);
        glVertex3f(-Tamanho, teto, -Tamanho);

        glColor3f(0.3f, 0, 0);
        //Lado da esqueda
        glVertex3f(Tamanho, piso, -Tamanho);
        glVertex3f(-Tamanho, piso,  -Tamanho);
        glVertex3f( -Tamanho, teto,  -Tamanho);
        glVertex3f( Tamanho, teto, -Tamanho);

        //Lado da Direita
        glVertex3f(Tamanho, piso, Tamanho);
        glVertex3f(-Tamanho, piso,  Tamanho);
        glVertex3f( -Tamanho, teto,  Tamanho);
        glVertex3f( Tamanho, teto, Tamanho);
    glEnd();*/

    glutSwapBuffers();
}

void Flight::reshape(GLint width, GLint height) 
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

void Flight::keyboard(GLubyte key, GLsizei x, GLsizei y) {
    switch(key) {
        case W:
        case w:
            observer.walk(1.0f);
            break;
        case A:
        case a:
            break;
        case S:
        case s:
            observer.walk(-1.0f);
            break;
        case D:
        case d:
            break;
        default:
        ;
    }
}

void Flight::special(GLint key, GLint x, GLint y) { 
    switch(key) {
        case UP_ARROW:
            observer.pitch(-1.0f);
            break;
        case DOWN_ARROW:
            observer.pitch(+1.0f);
            break;
        case LEFT_ARROW:
            observer.roll(-1.0f);
            break;
        case RIGHT_ARROW:
            observer.roll(+1.0f);
            break;
    }
}

void Flight::load() 
{
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

    // Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_AMBIENT, &lightAmbient[0]);
    // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, &lightDiffuse[0]);
    // Position The Light
    glLightfv(GL_LIGHT1, GL_POSITION, &lightPosition[0]);
    // Enable Light One
    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHTING);
}