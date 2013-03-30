#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "camera.h"
#include "object.h"

#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace glm;

class Controller {

private:
    
    GLfloat currentSpeed;
    GLfloat maxSpeed;
    GLfloat currentAcceleration;
    GLfloat maxAcceleration;
    Camera * camera;
    Object * plane;

public:

    Controller(Camera * camera, Object * plane);
    ~Controller() {}
    
    void setMaxSpeed(GLfloat speed);
    void setAcceleration(GLfloat acceleration);
    void moveFoward();
    void turnUp();
    void turnDown();
    void spinLeft();
    void spinRight();
    void update();    
};

#endif // CONTROLLER_H