#include "Object3D.h"

Object3D::Object3D(){
    matrix = glm::mat4(1.f);
    position = glm::vec3(0.f);
    scale = glm::vec3(1.f);
    rotation = glm::vec3(0.f);
}

Object3D::~Object3D(){
    //dtor
}
