#include "../headers/observer.h"
#include <iostream>
using namespace std;

void Observer::initialize(vec3 eye, vec3 center, vec3 upp) 
{
    this->origin = eye;
    this->axisZ = center - eye;
    this->axisY = upp - eye;
    this->axisX = cross(axisZ, axisY);
}

void Observer::pitch(GLfloat pitchAngle) 
{
    mat4 pitchMatrix(1.0f);

    translateToOrigin();

    pitchMatrix = rotate(pitchMatrix, pitchAngle, axisX);

    axisX = vec3(pitchMatrix * vec4(axisX, 1.0f));
    axisY = vec3(pitchMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(pitchMatrix * vec4(axisZ, 1.0f));

    translateBack();
}

void Observer::yaw(GLfloat yawAngle) 
{
    mat4 yawMatrix(1.0f);

    translateToOrigin();

    yawMatrix = rotate(yawMatrix, yawAngle, axisY);
    
    axisX = vec3(yawMatrix * vec4(axisX, 1.0f));
    axisY = vec3(yawMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(yawMatrix * vec4(axisZ, 1.0f));

    translateBack();
}

void Observer::roll(GLfloat rollAngle) 
{
    mat4 rollMatrix(1.0f);

    translateToOrigin();

    rollMatrix = rotate(rollMatrix, rollAngle, axisZ);

    axisX = vec3(rollMatrix * vec4(axisX, 1.0f));
    axisY = vec3(rollMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(rollMatrix * vec4(axisZ, 1.0f));

    translateBack();
}

void Observer::translateToOrigin() 
{
    axisX -=  origin;
    axisY -=  origin;
    axisZ -=  origin;
}

void Observer::translateBack() 
{
    axisX +=  origin;
    axisY +=  origin;
    axisZ +=  origin;
}

void Observer::walk(GLfloat distance)
{  
    vec3 direction = axisZ - origin;

    direction = normalize(direction);

    direction *= distance;

    origin += direction;
    axisX += direction;
    axisY += direction;
    axisZ += direction;
}

void Observer::setObserver() 
{
    view = lookAt(origin, axisZ, axisY - origin);
}

void Observer::debug() {
    cout << "ORIGIN" << endl;
    cout << origin[0] << "\t\t";
    cout << origin[1] << "\t\t";
    cout << origin[2] << endl;
    cout << "AXISX" << endl;
    cout << axisX[0] << "\t\t";
    cout << axisX[1] << "\t\t";
    cout << axisX[2] << endl;
    cout << "AXISY" << endl;
    cout << axisY[0] << "\t\t";
    cout << axisY[1] << "\t\t";
    cout << axisY[2] << endl;
    cout << "AXISZ" << endl;
    cout << axisZ[0] << "\t\t";
    cout << axisZ[1] << "\t\t";
    cout << axisZ[2] << endl;
}