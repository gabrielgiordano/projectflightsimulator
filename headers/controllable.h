#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace glm;

class Controllable {

private:

    
    /* CONTROLADOR GLfloat currentSpeed;
    GLfloat maxSpeed;
    GLfloat currentAcceleration;
    GLfloat maxAcceleration;*/

public:

    vec3 origin, axisX, axisY, axisZ;

    virtual void setCoordinateSystem(vec3 origin, vec3 axisX, vec3 axisY, vec3 axisZ) = 0;
    virtual void translate(vec3 distance) = 0;
    virtual void translateToOrigin() = 0;
    virtual void translateBack() = 0;
    virtual void translateInAxisX(GLfloat distance) = 0;
    virtual void translateInAxisY(GLfloat distance) = 0;
    virtual void translateInAxisZ(GLfloat distance) = 0;
    virtual void rotateInAxisX(GLfloat pitchAngle) = 0;
    virtual void rotateInAxisY(GLfloat yawAngle) = 0;
    virtual void rotateInAxisZ(GLfloat rollAngle) = 0;
};

#endif  