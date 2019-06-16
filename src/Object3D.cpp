#include "Object3D.h"

Object3D::Object3D(){
    matrix = glm::mat4(1.f);
    position = glm::vec3(0.f);
    scale = glm::vec3(1.f);
    rotation = glm::vec3(0.f);
}

Object3D::~Object3D(){}

void Object3D::setPosition(glm::vec3 p){
    position = p;

    combineTransformations();
}

void Object3D::setScale(glm::vec3 s){
    scale = s;

    combineTransformations();
}

void Object3D::addScale(glm::vec3 s){
    scale += s;

    combineTransformations();
}

void Object3D::setRotationFromEuler(glm::vec3 euler){
    rotation = euler;

    combineTransformations();
}

void Object3D::addRotationFromEuler(glm::vec3 euler){
    rotation += euler;

    combineTransformations();
}

void Object3D::combineTransformations(){
    glm::mat4 scaleMatrix = glm::scale(scale);

    float mat[16];
    float A = cos(rotation.x);
    float B = sin(rotation.x);
    float C = cos(rotation.y);
    float D = sin(rotation.y);
    float E = cos(rotation.z);
    float F = sin(rotation.z);

    float AD = A * D;
    float BD = B * D;

    mat[0]  =   C * E;
    mat[1]  =  -C * F;
    mat[2]  =   D;
    mat[4]  =  BD * E + A * F;
    mat[5]  = -BD * F + A * E;
    mat[6]  =  -B * C;
    mat[8]  = -AD * E + B * F;
    mat[9]  =  AD * F + B * E;
    mat[10] =   A * C;

    mat[3]  =  mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
    mat[15] =  1;
    glm::mat4 rotationMatrix = glm::make_mat4(mat);

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.f), position);

    matrix = translationMatrix * rotationMatrix * scaleMatrix;
}
