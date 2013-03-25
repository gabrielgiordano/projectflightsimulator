#ifndef OBSERVER_H
#define OBSERVER_H

#include <cmath>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Observer {

private:
	vec3 position;
	vec3 axisX, axisY, axisZ;
    vec3 translation;
    GLfloat pitchAngle, yawAngle, rollAngle;

public:
    
    mat4 view;

    Observer() {}
    ~Observer() {}    

    void initialize(vec3 eye, vec3 center, vec3 upp);
    void pitch(GLfloat pitch);
    void yaw(GLfloat yaw);
    void roll(GLfloat roll);
    void doRotations(vec3 &aux_AxisX, vec3 &aux_AxisY, vec3 &aux_AxisZ);
    void walk(vec3 distance);
    void setObserver();
};

#endif