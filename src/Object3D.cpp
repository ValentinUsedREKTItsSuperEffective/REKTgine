#include "Object3D.h"

#include <glm/gtx/norm.hpp>

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
    vec3 direction = normalize(obj.position - position);
    mat4 rotationMatrix = glm::toMat4(quaternion);

    // Without forcing the object to be straight
    quaternion = RotationBetweenVectors(vec3(rotationMatrix[2][0], rotationMatrix[2][1], rotationMatrix[2][2]), direction) * quaternion;

    // With forcing
    vec3 up = vec3(0.f, 1.f, 0.f);
    vec3 right = cross(direction, up);
    up = cross(right, direction);
    rotationMatrix = glm::toMat4(quaternion);

    quaternion = RotationBetweenVectors(vec3(rotationMatrix[1][0], rotationMatrix[1][1], rotationMatrix[1][2]), up) * quaternion;

    combineTransformations();
}

/**
 ** Protected functions
 **/
// https://github.com/opengl-tutorials/ogl/blob/master/common/quaternion_utils.cpp
// Returns a quaternion such that q*start = dest
quat Object3D::RotationBetweenVectors(vec3 start, vec3 dest){
    start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions :
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		// This implementation favors a rotation around the Up axis,
		// since it's often what you want to do.
		rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
			rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return angleAxis(glm::radians(180.0f), rotationAxis);
	}

	// Implementation from Stan Melax's Game Programming Gems 1 article
	rotationAxis = cross(start, dest);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

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
