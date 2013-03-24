#ifndef FLIGHT_H
#define FLIGHT_H

#include <cmath>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "framework.h"
#include "observer.h"
#include "SOIL.h"

class Flight : public Framework
{
private:
    Observer observer;

    glm::vec4 lightAmbient;
    glm::vec4 lightDiffuse;
    glm::vec4 lightPosition;

    GLdouble deepOnZ;
    GLuint * texture;
    
public:
    Flight();
    ~Flight() {}
    bool loadTextures();

    virtual void display();
    virtual void reshape(GLint width, GLint height);
    virtual void keyboard(GLubyte key, GLint x, GLint y);
    virtual void special(GLint key, GLint x, GLint y);
    virtual void mouse(GLsizei button, GLsizei state, GLsizei x, GLsizei y) {}
    virtual void time(GLint value) {}
    virtual void load();
};

#endif // FLIGHT_H