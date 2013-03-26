#include "../headers/observer.h"
#include <iostream>
using namespace std;

void Observer::initialize(vec3 eye, vec3 center, vec3 upp) 
{
    this->position = eye;
    this->axisZ = center - eye;
    this->axisY = upp - eye;
    this->axisX = cross(axisZ, axisY);
    this->upp = upp;
}

void Observer::pitch(GLfloat pitchAngle) 
{
    mat4 pitchMatrix(1.0f);
    pitchMatrix = rotate(pitchMatrix, pitchAngle, axisX - position);

    axisY = vec3(pitchMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(pitchMatrix * vec4(axisZ, 1.0f));
    upp   = vec3(pitchMatrix * vec4(upp, 1.0f));
}

void Observer::yaw(GLfloat yawAngle) 
{
    mat4 yawMatrix(1.0f);
    yawMatrix = rotate(yawMatrix, yawAngle, axisY - position);

    axisX = vec3(yawMatrix * vec4(axisX, 1.0f));
    axisZ = vec3(yawMatrix * vec4(axisZ, 1.0f));
}

void Observer::roll(GLfloat rollAngle) 
{
    mat4 rollMatrix(1.0f);
    rollMatrix = rotate(rollMatrix, rollAngle, axisZ - position);

    axisX = vec3(rollMatrix * vec4(axisX, 1.0f));
    axisY = vec3(rollMatrix * vec4(axisY, 1.0f));
    upp   = vec3(rollMatrix * vec4(upp, 1.0f));
}

void Observer::walk(GLfloat distance)
{  
    vec3 direction = axisZ - position;

    direction = normalize(direction);

    direction *= distance;

    cout << "direction" << endl;
    cout << direction[0] << "\t\t";
    cout << direction[1] << "\t\t";
    cout << direction[2] << endl;


    position += direction;
    axisX += direction;
    axisY += direction;
    axisZ += direction;
    debug();
}

void Observer::setObserver() 
{
    view = lookAt(position, axisZ, upp);
}

void Observer::debug() {
    cout << "POSITION" << endl;
    cout << position[0] << "\t\t";
    cout << position[1] << "\t\t";
    cout << position[2] << endl;
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
    cout << "UPP" << endl;
    cout << upp[0] << "\t\t";
    cout << upp[1] << "\t\t";
    cout << upp[2] << endl;
}