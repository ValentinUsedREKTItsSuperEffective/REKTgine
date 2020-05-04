#include "Object3D.h"

Object3D::Object3D() : name(""), model(mat4(1.f)), position(vec3()), scale(vec3(1.f)), rotation(vec3()) {}

Object3D::~Object3D(){}

void Object3D::SetParent(Object3D &parent){
    this->parent = &parent;
    parent.AddChildren(this);
}

void Object3D::AddChildren(Object3D* child){
    children.push_back(child);
}

void Object3D::setPosition(vec3 p){
    position = p;

    combineTransformations();
}

void Object3D::setPosition(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;

    combineTransformations();
}

void Object3D::addPosition(vec3 p){
    position += p;

    combineTransformations();
}

void Object3D::setScale(vec3 s){
    scale = s;

    combineTransformations();
}

void Object3D::setScale(float scale){
    this->scale.x = this->scale.y = this->scale.z = scale;

    combineTransformations();
}

void Object3D::addScale(vec3 s){
    scale += s;

    combineTransformations();
}

void Object3D::setRotationFromEuler(vec3 euler){
    rotation = euler;

    combineTransformations();
}

void Object3D::addRotationFromEuler(vec3 euler){
    rotation += euler;

    combineTransformations();
}

void Object3D::rotateAroundPoint(vec3 point, vec3 euler){
    combineTransformations();

    model = translate(point) * eulerToMat4(euler) * translate(-point) * model;

    position.x = model[3][0];
    position.y = model[3][1];
    position.z = model[3][2];

    // TODO : Actualize Euler
}

mat4 Object3D::eulerToMat4(vec3 euler){
    float mat[16];
    float A = cos(euler.x);
    float B = sin(euler.x);
    float C = cos(euler.y);
    float D = sin(euler.y);
    float E = cos(euler.z);
    float F = sin(euler.z);

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
    return make_mat4(mat);
}

void Object3D::combineTransformations(){
    mat4 scaleMatrix = glm::scale(scale);

    mat4 rotationMatrix = eulerToMat4(rotation);

    mat4 translationMatrix = translate(mat4(1.f), position);

    model = translationMatrix * rotationMatrix * scaleMatrix;
}
