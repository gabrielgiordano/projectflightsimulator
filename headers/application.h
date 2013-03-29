#ifndef APPLICATION_H
#define APPLICATION_H

#include "framework.h"
#include "../headers/object.h"

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Application : public Framework
{

private:
    
    Object object;
    vec4 lightAmbient;
    vec4 lightDiffuse;
    vec4 lightPosition;
    
public:
    
    Application();
    ~Application() {}

    virtual void display();
    virtual void reshape(GLint width, GLint height);
    virtual void keyboard(GLubyte key, GLint x, GLint y);
    virtual void special(GLint key, GLint x, GLint y);
    virtual void mouse(GLsizei button, GLsizei state, GLsizei x, GLsizei y) {}
    virtual void time(GLint value) {}
    virtual void load();
};

#endif // APPLICATION_H