#ifndef OBJECT_H
#define OBJECT_H

#include "controllable.h"
#include <glm.h>
#include <SOIL.h>

#include <iostream>
#include <string.h>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

class Object : public Controllable {

private:

    GLMmodel * model;
    GLuint texture;

    mat4 translation;
    mat4 rotation;

public:   

    Object();
    ~Object();

    void loadOBJ(string filename);
    void loadTexture(string filename);
    void draw();

    void setCoordinateSystem(vec3 origin, vec3 axisX, vec3 axisY, vec3 axisZ);
    void translate(vec3 distance);
    void translateToOrigin();
    void translateBack();
    void translateInAxisX(GLfloat distance);
    void translateInAxisY(GLfloat distance);
    void translateInAxisZ(GLfloat distance);
    void rotateInAxisX(GLfloat pitchAngle);
    void rotateInAxisY(GLfloat yawAngle);
    void rotateInAxisZ(GLfloat rollAngle);

};

#endif
