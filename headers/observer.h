#ifndef OBSERVER_H
#define OBSERVER_H

#include <cmath>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Observer {

private:

    glm::vec3 normal, upp, cross;

public:
    
    glm::mat4 view;

    Observer() {}
    ~Observer() {}    

    void initialize(glm::vec3 eye, glm::vec3 center, glm::vec3 upp);
    void walk(glm::vec3 distance);
    void pitch(GLfloat pitch);
    void yaw(GLfloat yaw);
    void roll(GLfloat roll);
};

#endif