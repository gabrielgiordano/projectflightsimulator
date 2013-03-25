#include "../headers/observer.h"

void Observer::initialize(vec3 eye, vec3 center, vec3 upp) 
{
    position = eye;
    axisZ = center - eye;
    axisY = upp - eye;
    axisX = cross(axisZ, axisY);

    pitchAngle = yawAngle = rollAngle = 0.0f;
    translation = vec3(0.0f, 0.0f, 0.0f);
}

void Observer::pitch(GLfloat pitch) {pitchAngle += pitch;}

void Observer::yaw(GLfloat yaw) {yawAngle += yaw;}

void Observer::roll(GLfloat roll) {rollAngle += roll;}

void Observer::doRotations(vec3 &aux_AxisX, vec3 &aux_AxisY, vec3 &aux_AxisZ)
{
    mat4 pitchMatrix(1.0f), yawMatrix(1.0f), rollMatrix(1.0f);

    pitchMatrix = rotate(pitchMatrix, pitchAngle, axisX);
    yawMatrix = rotate(yawMatrix, yawAngle, axisY);
    rollMatrix = rotate(rollMatrix, rollAngle, axisZ);

    // Apply the pitch rotation
    aux_AxisY = vec3(pitchMatrix * vec4(axisY, 1.0f));
    aux_AxisZ = vec3(pitchMatrix * vec4(axisZ, 1.0f));

    // Apply the yaw rotation
    aux_AxisX = vec3(yawMatrix * vec4(axisX, 1.0f));
    aux_AxisZ = vec3(yawMatrix * vec4(axisZ, 1.0f));

    // Apply the roll rotation
    aux_AxisX = vec3(rollMatrix * vec4(axisX, 1.0f));
    aux_AxisY = vec3(rollMatrix * vec4(axisY, 1.0f));
}

void Observer::walk(vec3 distance)
{
    vec3 aux_AxisX, aux_AxisY, aux_AxisZ;

    aux_AxisX = aux_AxisY = aux_AxisZ = vec3(0.0f, 0.0f, 0.0f);
    
    doRotations(aux_AxisX, aux_AxisY, aux_AxisZ);

    aux_AxisZ = normalize(aux_AxisZ);

    translation = aux_AxisZ * distance;
    
}

void Observer::setObserver() 
{
    vec3 aux_AxisX, aux_AxisY, aux_AxisZ, upp;

    aux_AxisX = aux_AxisY = aux_AxisZ = vec3(0.0f, 0.0f, 0.0f);
    
    doRotations(aux_AxisX, aux_AxisY, aux_AxisZ);

    upp = aux_AxisY;
    // Apply translations
    position  += translation;
    aux_AxisX += translation;
    aux_AxisY += translation;
    aux_AxisZ += translation;

    view = lookAt(position, aux_AxisZ, upp);
}