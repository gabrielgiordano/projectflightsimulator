#include "../headers/camera.h"

Camera::Camera(vec3 eye, vec3 center, vec3 upp) 
{
    this->origin = eye;
    this->axisZ = center - eye;
    this->axisY = upp - eye;
    this->axisX = cross(axisZ, axisY);
}


void Camera::setCoordinateSystem(vec3 origin, vec3 axisX, vec3 axisY, vec3 axisZ) 
{
    this->origin = origin;
    this->axisX = axisX;
    this->axisY = axisY;
    this->axisZ = axisZ;
}

void Camera::translate(vec3 distance) 
{
    this->origin += distance;
    this->axisX += distance;
    this->axisY += distance;
    this->axisZ += distance;
}

void Camera::translateToOrigin()
{
    axisX -=  origin;
    axisY -=  origin;
    axisZ -=  origin;
}

void Camera::translateBack()
{
    axisX +=  origin;
    axisY +=  origin;
    axisZ +=  origin;
}

void Camera::translateInAxisX(GLfloat distance)
{  
    vec3 direction = axisX - origin;

    direction = normalize(direction);

    direction *= distance;

    origin += direction;
    axisX += direction;
    axisY += direction;
    axisZ += direction;
}

void Camera::translateInAxisY(GLfloat distance)
{  
    vec3 direction = axisY - origin;

    direction = normalize(direction);

    direction *= distance;

    origin += direction;
    axisX += direction;
    axisY += direction;
    axisZ += direction;
}

void Camera::translateInAxisZ(GLfloat distance)
{  
    vec3 direction = axisZ - origin;

    direction = normalize(direction);

    direction *= distance;

    origin += direction;
    axisX += direction;
    axisY += direction;
    axisZ += direction;
}

void Camera::rotateInAxisX(GLfloat pitchAngle) 
{
    mat4 pitchMatrix(1.0f);

    translateToOrigin();

    pitchMatrix = rotate(pitchMatrix, pitchAngle, axisX);

    axisX = vec3(pitchMatrix * vec4(axisX, 1.0f));
    axisY = vec3(pitchMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(pitchMatrix * vec4(axisZ, 1.0f));

    translateBack();
}

void Camera::rotateInAxisY(GLfloat yawAngle)
{
    mat4 yawMatrix(1.0f);

    translateToOrigin();

    yawMatrix = rotate(yawMatrix, yawAngle, axisY);
    
    axisX = vec3(yawMatrix * vec4(axisX, 1.0f));
    axisY = vec3(yawMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(yawMatrix * vec4(axisZ, 1.0f));

    translateBack();
}

void Camera::rotateInAxisZ(GLfloat rollAngle) 
{
    mat4 rollMatrix(1.0f);

    translateToOrigin();

    rollMatrix = rotate(rollMatrix, rollAngle, axisZ);

    axisX = vec3(rollMatrix * vec4(axisX, 1.0f));
    axisY = vec3(rollMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(rollMatrix * vec4(axisZ, 1.0f));

    translateBack();
}

void Camera::setCamera()
{
    view = lookAt(origin, axisZ, axisY - origin);
}