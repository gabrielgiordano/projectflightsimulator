#include "../headers/controller.h"

Controller::Controller(Camera * camera, Object * plane)
{
    this->camera = camera;
    this->plane = plane;
    maxSpeed = 0.5f;
    currentSpeed = 0.0f;
    currentAcceleration = 0.0f;
}

void Controller::setMaxSpeed(GLfloat speed)
{
    maxSpeed = speed;
}

void Controller::setAcceleration(GLfloat acceleration)
{
    maxAcceleration = acceleration;
}

void Controller::moveFoward()
{
    plane->translateInAxisZ(1.0f * currentSpeed);
    camera->translateInAxisZ(1.0f * currentSpeed);
}

void Controller::turnUp()
{

}

void Controller::turnDown()
{

}

void Controller::spinLeft()
{

}

void Controller::spinRight()
{

}

void Controller::update()
{

}
