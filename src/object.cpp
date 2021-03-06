#include "../headers/object.h"

Object::Object()
{
    model = NULL;
    //texture = 0;
    mode = 0;
    transformations = mat4(1.0f);
    this->origin = vec3(0.0f, 0.0f, 0.0f);
    this->axisX = vec3(1.0f, 0.0f, 0.0f);
    this->axisY = vec3(0.0f, 1.0f, 0.0f);
    this->axisZ = vec3(0.0f, 0.0f, -1.0f);
}

Object::~Object()
{
    glmDelete(model);
}

void Object::loadOBJ(string filename) 
{

    if(filename.size() == 0)
    {
        cerr << "OBJ filename is empty.";
        exit(1);
    }

    char * OBJFilename = new char[filename.size() + 1];
    strcpy(OBJFilename, filename.c_str());

    model = glmReadOBJ(OBJFilename);
    if (!model) 
    {
        cerr << "Unable to load the model " << OBJFilename;
        exit(1);
    }

    glmUnitize(model);
    // These 2 functions calculate triangle and vertex normals from the geometry data.
    // To be honest I had some problem with very complex models that didn't look to good because of how vertex normals were calculated
    // So if you can export these directly from you modeling tool do it and comment these line
    // 3DS Max can calculate these for you and GLM is perfectly capable of loading them
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0, GL_TRUE);
}

/*void Object::loadTexture(string filename)
{ 
    if(filename.size() == 0)
    {
        cerr << "Texture filename is empty.";
        exit(1);
    }

    char * textureFilename = new char[filename.size() + 1];
    strcpy(textureFilename, filename.c_str());

    // load an image file directly as a new OpenGL texture
    texture = SOIL_load_OGL_texture
        (
            textureFilename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
        );
 
    if(texture == 0) {
        cerr << "Unable to load texture " << textureFilename; 
        exit(1);
    }
 
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}*/

void Object::draw() {

    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    
    glMultMatrixf(&transformations[0][0]);

    /*if(texture)
        glBindTexture(GL_TEXTURE_2D, texture);*/

    glmDraw(model, mode);

    glPopMatrix();
}

void Object::scale(GLfloat factor) 
{
    glmScale(model, factor);
}

void Object::setDrawMode(GLboolean smooth, GLboolean texture, GLboolean material) 
{
    if(smooth)
        mode |= GLM_SMOOTH;
    if(texture)
        mode |= GLM_TEXTURE;
    if(material)
        mode |= GLM_MATERIAL;
}

void Object::setCoordinateSystem(vec3 origin, vec3 axisX, vec3 axisY, vec3 axisZ) 
{
    transformations = mat4(1.0f);
    this->origin = origin;
    this->axisX = axisX;
    this->axisY = axisY;
    this->axisZ = axisZ;
}

void Object::translate(vec3 distance)
{
    if(model) {
        this->origin += distance;
        this->axisX += distance;
        this->axisY += distance;
        this->axisZ += distance;

        mat4 translation(1.0f);

        translation = glm::translate(translation, distance);
        transformations = translation * transformations;
    }
    else {
        cerr << "Calling translate in object without any model loaded.";
        exit(1);
    }
}

void Object::translateInAxisX(GLfloat distance)
{
    vec3 direction = axisX - origin;

    direction = normalize(direction);

    direction *= distance;

    origin += direction;
    axisX += direction;
    axisY += direction;
    axisZ += direction;

    mat4 translation(1.0f);
    
    translation = glm::translate(translation, direction);
    transformations = translation * transformations;
}

void Object::translateInAxisY(GLfloat distance)
{  
    vec3 direction = axisY - origin;

    direction = normalize(direction);

    direction *= distance;

    origin += direction;
    axisX += direction;
    axisY += direction;
    axisZ += direction;

    mat4 translation(1.0f);
    
    translation = glm::translate(translation, direction);
    transformations = translation * transformations;
}

void Object::translateInAxisZ(GLfloat distance)
{  
    vec3 direction = axisZ - origin;

    direction = normalize(direction);

    direction *= distance;

    origin += direction;
    axisX += direction;
    axisY += direction;
    axisZ += direction;

    mat4 translation(1.0f);
    
    translation = glm::translate(translation, direction);
    transformations = translation * transformations;
}

void Object::rotateInAxisX(GLfloat pitchAngle) 
{
    mat4 pitchMatrix(1.0f);
    vec3 origin_aux = origin;
    
    translate(-origin_aux);

    pitchMatrix = rotate(pitchMatrix, pitchAngle, axisX);   

    axisX = vec3(pitchMatrix * vec4(axisX, 1.0f));
    axisY = vec3(pitchMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(pitchMatrix * vec4(axisZ, 1.0f));

    transformations = pitchMatrix * transformations;

    translate(origin_aux);
}

void Object::rotateInAxisY(GLfloat yawAngle)
{
    mat4 yawMatrix(1.0f);
    vec3 origin_aux = origin;
    
    translate(-origin_aux);

    yawMatrix = rotate(yawMatrix, yawAngle, axisY);
    
    axisX = vec3(yawMatrix * vec4(axisX, 1.0f));
    axisY = vec3(yawMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(yawMatrix * vec4(axisZ, 1.0f));

    transformations = yawMatrix * transformations;

    translate(origin_aux);
}

void Object::rotateInAxisZ(GLfloat rollAngle) 
{
    mat4 rollMatrix(1.0f);
    vec3 origin_aux = origin;
    
    translate(-origin_aux);

    rollMatrix = rotate(rollMatrix, rollAngle, axisZ);

    axisX = vec3(rollMatrix * vec4(axisX, 1.0f));
    axisY = vec3(rollMatrix * vec4(axisY, 1.0f));
    axisZ = vec3(rollMatrix * vec4(axisZ, 1.0f));

    transformations = rollMatrix * transformations;

    translate(origin_aux);
}

void Object::getCoordinateSystem(vec3 * coordinate) 
{    
    coordinate[0] = origin;
    coordinate[1] = axisX;
    coordinate[2] = axisY;
    coordinate[3] = axisZ;
}