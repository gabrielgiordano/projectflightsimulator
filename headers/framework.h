#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "stopwatch.h"
#include <string>

#ifdef FRAMEWORK_USE_GLEW
    #include <GL/glew.h>
#endif

#include <GL/glut.h>

using namespace std;

class Framework {

private:

    double frameTimeElapsed;

protected:

    string title;
    GLboolean fullScreen;
    Stopwatch frameRateTimer;
    static Framework *instance;

public:

    const static GLint FPS = 60;
    const static GLint WINDOW_WIDTH = 500;
    const static GLint WINDOW_HEIGHT = 500;
    const static GLint WINDOW_X_POSITION = 100;
    const static GLint WINDOW_Y_POSITION = 100;
    const static GLdouble FRAME_TIME;

    Framework();
    virtual ~Framework();

    void startFramework(int argc, char *argv[]);
    void setInstance();
    void setInstance(Framework * framework);
    Framework* getInstance();
    void setFullScreen(GLboolean option);
    void setTitle(string title);
    void init();
    void run();

    virtual void display();
    virtual void reshape(GLint width, GLint height);
    virtual void keyboard(GLubyte key, GLint x, GLint y);
    virtual void special(GLint key, GLint x, GLint y);
    virtual void mouse(GLsizei button, GLsizei state, GLsizei x, GLsizei y);
    virtual void time(GLint value);
    virtual void load();

    static void runWrapper();
    static void displayWrapper();
    static void reshapeWrapper(GLint width, GLint height);
    static void keyboardWrapper(GLubyte key, GLint x, GLint y);
    static void specialWrapper(GLint key, GLint x, GLint y);
    static void mouseWrapper(GLsizei button, GLsizei state, GLsizei x, GLsizei y);
    static void timeWrapper(GLint value);
};

#endif // FRAMEWORK_H
