#ifndef OBSERVER_H
#define OBSERVER_H

#include <cmath>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Observer {

private:

    vec3 position, axisZ, axisY, axisX;
    vec3 upp;

public:
    
    mat4 view;

    Observer() {}
    ~Observer() {}    

    void initialize(vec3 eye, vec3 center, vec3 upp);
    void pitch(GLfloat pitchAngle);
    void yaw(GLfloat yawAngle);
    void roll(GLfloat rollAngle);
    void walk(GLfloat distance);
    void setObserver();
    void debug();
};

#endif