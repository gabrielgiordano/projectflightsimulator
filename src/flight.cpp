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
    
    deepOnZ = -6.0f;
    texture = new GLuint[1];

    lightAmbient = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    lightDiffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    lightPosition = glm::vec4(0.0f, 0.0f, 5.0f, 1.0f);
}

bool Flight::loadTextures() 
{
    texture[0] = SOIL_load_OGL_texture
                (
                    "textures/NeHe.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y
                );

    if(texture[0] == 0) {
        cout << "Texture not loaded!!\n";
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;

}

void Flight::display ()
{
    // Clear The Screen And The Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset The Current Modelview Matrix
    glLoadIdentity();
    observer.setObserver();
    glMultMatrixf(&observer.view[0][0]);

    // Move Left 1.5 Units And Into The Screen 6.0
    glTranslatef(0.0f, 0.0f, deepOnZ);

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);
        // Front Face
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
        // Back Face
        glNormal3f( 0.0f, 0.0f,-1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
        // Top Face
        glNormal3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
        // Bottom Face
        glNormal3f( 0.0f,-1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
        // Right face
        glNormal3f( 1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
        // Left Face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glEnd();

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
    gluPerspective(45.0f,(GLdouble)width/(GLdouble)height,0.1f,100.0f);

    // Select The Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Flight::keyboard(GLubyte key, GLsizei x, GLsizei y) {
    switch(key) {
        case W:
        case w:
            observer.walk(glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        case A:
        case a:
            break;
        case S:
        case s:
            observer.walk(glm::vec3(0.0f, 0.0f, -1.0f));
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
            observer.roll(+1.0f);
            break;
        case RIGHT_ARROW:
            observer.roll(-1.0f);
            break;
    }
}

void Flight::load() 
{
    if (loadTextures()) {
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
}