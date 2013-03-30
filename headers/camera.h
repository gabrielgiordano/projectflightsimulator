#ifndef CAMERA_H
#define CAMERA_H

#include "controllable.h"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera : public Controllable {

public:
    
    mat4 view;

    Camera(vec3 eye, vec3 center, vec3 upp);
    ~Camera() {}

    void setCamera();

    void setCoordinateSystem(vec3 origin, vec3 axisX, vec3 axisY, vec3 axisZ);
    void translate(vec3 distance);
    void translateInAxisX(GLfloat distance);
    void translateInAxisY(GLfloat distance);
    void translateInAxisZ(GLfloat distance);
    void rotateInAxisX(GLfloat pitchAngle);
    void rotateInAxisY(GLfloat yawAngle);
    void rotateInAxisZ(GLfloat rollAngle);
    void getCoordinateSystem(vec3 * coordinate);

};

#endif // CAMERA_H