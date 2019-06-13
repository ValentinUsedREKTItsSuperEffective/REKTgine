#include "Camera.h"

#define M_PI 3.14159265358979323846

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 axis) : Object3D(), _theta(0.), _phi(0.), _orientation(), _axis(axis), _sideDisplacement(), _target(target), _sensibility(0.5f), _speed(0.5f){
    Object3D::SetPosition(position);
    setTarget(target);
}

Camera::~Camera(){}

void Camera::orientate(int xRel, int yRel){
    _phi += -yRel * _sensibility;
    _theta += -xRel * _sensibility;

    if(_phi > 89.)
        _phi = 89.;
    else if(_phi < -89.)
        _phi = -89.;

    float radPhi = _phi * M_PI / 180;
    float radTheta = _theta * M_PI / 180;

    if(_axis.x == 1.0){
        _orientation.x = sin(radPhi);
        _orientation.y = cos(radPhi) * cos(radTheta);
        _orientation.z = cos(radPhi) * sin(radTheta);
    } else if(_axis.y == 1.0){
        _orientation.x = cos(radPhi) * sin(radTheta);
        _orientation.y = sin(radPhi);
        _orientation.z = cos(radPhi) * cos(radTheta);
    } else {
        _orientation.x = cos(radPhi) * cos(radTheta);
        _orientation.y = cos(radPhi) * sin(radTheta);
        _orientation.z = sin(radPhi);
    }

    _sideDisplacement = glm::normalize(glm::cross(_axis, _orientation));

    _target = position + _orientation;
}

void Camera::translate(Input const &input){
    if(input.inMovement()){
        orientate(input.mouseRX, input.mouseRY);
    }

    if(input.getKey(SDL_SCANCODE_UP)){
        SetPosition(position + _orientation * _speed);
        _target = position + _orientation;
    }

    if(input.getKey(SDL_SCANCODE_DOWN)){
        SetPosition(position - _orientation * _speed);
        _target = position + _orientation;
    }

    if(input.getKey(SDL_SCANCODE_LEFT)){
        SetPosition(position + _sideDisplacement * _speed);
        _target = position + _orientation;
    }

    if(input.getKey(SDL_SCANCODE_RIGHT)){
        SetPosition(position - _sideDisplacement * _speed);
        _target = position + _orientation;
    }
}

void Camera::lookAt(glm::mat4 &modelView){
    modelView = glm::lookAt(position, _target, _axis);
}

void Camera::setTarget(glm::vec3 target){
    _orientation = glm::normalize(target - position);

    if(_axis.x == 1.0){
        _phi = asin(_orientation.x);
        _theta = acos(_orientation.y / cos(_phi));

        if(_orientation.y < 0)
            _theta *= -1;
    } else if(_axis.y == 1.0){
        _phi = asin(_orientation.y);
        _theta = acos(_orientation.z / cos(_phi));

        if(_orientation.z < 0)
            _theta *= -1;
    } else {
        _phi = asin(_orientation.z);
        _theta = acos(_orientation.x / cos(_phi));

        if(_orientation.x < 0)
            _theta *= -1;
    }

    _phi = _phi * 180. / M_PI;
    _theta = _theta * 180. / M_PI;
}

void Camera::SetPosition(glm::vec3 position){
    Object3D::SetPosition(position);

    _target = position + _orientation;
}

void Camera::setSensibility(float sensibility){
    _sensibility = sensibility;
}

void Camera::setSpeed(float speed){
    _speed = speed;
}
