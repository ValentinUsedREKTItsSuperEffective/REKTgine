#include "Object3D.h"

#include <iostream>

/**
 ** Public functions
 **/
Object3D::Object3D() : name(""), model(mat4(1.f)), position(vec3()), scale(vec3(1.f)), rotation(vec3()), quaternion(1, 0, 0, 0) {}

Object3D::~Object3D(){}

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

void Object3D::setRotationFromEuler(vec3 euler){ // euler in radians
    rotation = euler;
    quaternion = quat(rotation);

    combineTransformations();
}

void Object3D::addRotationFromEuler(vec3 euler){ // euler in radians
    rotation += euler;
    quaternion = quat(rotation);

    combineTransformations();
}

void Object3D::rotateAroundPoint(vec3 point, vec3 euler){
    position = point + quat(euler) * (position - point);
    //if(stationary){
    //    combineTransformations();
    //} else {
    addRotationFromEuler(euler);
    //}
}

void Object3D::LookAt(Object3D const &obj){
    vec3 fwd = normalize(obj.position - position); // forward

    vec3 up; // reference up vector
    if(fabs(fwd.x) < EPSILON && fabs(fwd.z) < EPSILON ){
            if(fwd.y > 0){
                up = vec3(0, 0, -1);
            } else {
                up = vec3(0, 0, 1);
            }
    } else {
        up = vec3(0, 1, 0);
    }
    vec3 left = normalize(cross(up, fwd));

    up = normalize(cross(fwd, left));

    float mat[16];
    mat[0]  = left.x;
    mat[1]  = left.y;
    mat[2]  = left.z;

    mat[4]  = up.x;
    mat[5]  = up.y;
    mat[6]  = up.z;

    mat[8]  = fwd.x;
    mat[9]  = fwd.y;
    mat[10] = fwd.z;

    mat[3]  =  mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
    mat[15] =  1;
}

/**
 ** Protected functions
 **/
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

    mat4 rotationMatrix = glm::toMat4(quaternion);

    mat4 translationMatrix = glm::translate(mat4(1.f), position);

    model = translationMatrix * rotationMatrix * scaleMatrix;
}

void Object3D::DebugMatrix(){
    if(!debug) return;

    std::cout << name << std::endl;
    std::cout << "Local matrix" << std::endl <<
    model[0][0] << "  " << model[1][0] << "  " << model[2][0] << "  " << model[3][0] << std::endl <<
    model[0][1] << "  " << model[1][1] << "  " << model[2][1] << "  " << model[3][1] << std::endl <<
    model[0][2] << "  " << model[1][2] << "  " << model[2][2] << "  " << model[3][2] << std::endl <<
    model[0][3] << "  " << model[1][3] << "  " << model[2][3] << "  " << model[3][3] << std::endl << std::endl;
}
