#include "../headers/observer.h"
#include <iostream>
using namespace std;

void Observer::initialize(glm::vec3 eye, glm::vec3 center, glm::vec3 upp) 
{
    this->normal = center - eye;
    this->upp = upp - center;
    this->cross = glm::cross(this->normal, this->upp);

    view = glm::lookAt(eye, center, upp);
}

void Observer::walk(glm::vec3 distance)
{
    glm::mat4 translate(1.0f);
    
    translate = glm::translate(translate, distance);

    normal = glm::vec3(translate * glm::vec4(normal, 1.0f));
    upp = glm::vec3(translate * glm::vec4(upp, 1.0f));
    cross = glm::vec3(translate * glm::vec4(cross, 1.0f));

    view = view * translate;
}

void Observer::pitch(GLfloat pitch) 
{
    glm::mat4 rotate(1.0f);
    
    rotate = glm::rotate(rotate, pitch, cross);

    normal = glm::vec3(rotate * glm::vec4(normal, 1.0f));
    upp = glm::vec3(rotate * glm::vec4(upp, 1.0f));

    view = view * rotate;
}

void Observer::yaw(GLfloat yaw) 
{
    glm::mat4 rotate(1.0f);
    
    rotate = glm::rotate(rotate, yaw, upp);

    normal = glm::vec3(rotate * glm::vec4(normal, 1.0f));
    cross = glm::vec3(rotate * glm::vec4(cross, 1.0f));

    view = view * rotate;
}

void Observer::roll(GLfloat roll) 
{
    glm::mat4 rotate(1.0f);

    rotate = glm::rotate(rotate, roll, normal);

    upp = glm::vec3(rotate * glm::vec4(upp, 1.0f));
    cross = glm::vec3(rotate * glm::vec4(cross, 1.0f));

    view = view * rotate;
}
