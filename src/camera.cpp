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
    vec3 origin_aux = origin;

    translate(-origin_aux);

    pitchMatrix = rotate(pitchMatrix, pitchAngle, axisX);

    axisX = vec3(pitchMatrix * vec4(axisX, 1.0f));
    axisY = vec3(pitchMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(pitchMatrix * vec4(axisZ, 1.0f));

    translate(origin_aux);
}

void Camera::rotateInAxisY(GLfloat yawAngle)
{
    mat4 yawMatrix(1.0f);
    vec3 origin_aux = origin;
    
    translate(-origin_aux);

    yawMatrix = rotate(yawMatrix, yawAngle, axisY);
    
    axisX = vec3(yawMatrix * vec4(axisX, 1.0f));
    axisY = vec3(yawMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(yawMatrix * vec4(axisZ, 1.0f));

    translate(origin_aux);
}

void Camera::rotateInAxisZ(GLfloat rollAngle) 
{
    mat4 rollMatrix(1.0f);
    vec3 origin_aux = origin;

    translate(-origin_aux);

    rollMatrix = rotate(rollMatrix, rollAngle, axisZ);

    axisX = vec3(rollMatrix * vec4(axisX, 1.0f));
    axisY = vec3(rollMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(rollMatrix * vec4(axisZ, 1.0f));

    translate(origin_aux);
}

void Camera::getCoordinateSystem(vec3 * coordinate) 
{    
    coordinate[0] = origin;
    coordinate[1] = axisX;
    coordinate[2] = axisY;
    coordinate[3] = axisZ;
}

void Camera::setCamera()
{
    view = lookAt(origin, axisZ, axisY - origin);
}

