#ifndef FLIGHT_H
#define FLIGHT_H

#include "framework.h"

struct Point
{
    GLfloat x, y, z;
};

class Flight : public Framework
{
private:
    Point eye;
    Point look;
    Point upp;
public:
    Flight();
    ~Flight() {}
    virtual void display();
    virtual void reshape(GLint width, GLint height);
    virtual void keyboard(GLubyte key, GLint x, GLint y);
    virtual void special(GLint key, GLint x, GLint y) {}
    virtual void mouse(GLsizei button, GLsizei state, GLsizei x, GLsizei y);
    virtual void time(GLint value) {}
    virtual void load();
};

#endif // FLIGHT_H