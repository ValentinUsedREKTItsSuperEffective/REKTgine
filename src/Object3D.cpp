#include "Object3D.h"

Object3D::Object3D(){
    matrix = glm::mat4(1.f);
    position = glm::vec3(0.f);
    scale = glm::vec3(1.f);
    rotation = glm::vec3(0.f);
}

Object3D::~Object3D(){}

void Object3D::SetPosition(glm::vec3 p){
    position = p;

    CombineTransformations();
}

void Object3D::CombineTransformations(){
    matrix = glm::translate(matrix, position);
}
