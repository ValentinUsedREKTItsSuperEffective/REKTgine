#include "Camera.h"

#define M_PI 3.14159265358979323846

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up) : Object3D(), _theta(0.), _phi(0.), _orientation(), _axis(up), sensibility(0.5f), speed(0.5f){
    Object3D::setPosition(position);

    setTarget(target);
}

Camera::~Camera(){}

void Camera::orientate(int xRel, int yRel){
    _phi += -yRel * sensibility;
    _theta += -xRel * sensibility;

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

    sideDisplacement = glm::normalize(glm::cross(_axis, _orientation));

    target = position + _orientation;
}

void Camera::translate(Input const &input){
    if(input.inMovement()){
        orientate(input.mouseRX, input.mouseRY);
    }

    if(input.getKey(SDL_SCANCODE_UP)){
        setPosition(position + _orientation * speed);
    }

    if(input.getKey(SDL_SCANCODE_DOWN)){
        setPosition(position - _orientation * speed);
    }

    if(input.getKey(SDL_SCANCODE_LEFT)){
        setPosition(position + sideDisplacement * speed);
    }

    if(input.getKey(SDL_SCANCODE_RIGHT)){
        setPosition(position - sideDisplacement * speed);
    }
}

void Camera::lookAt(glm::mat4 &view){
    view = glm::lookAt(position, target, _axis);
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

void Camera::setPosition(glm::vec3 position){
    Object3D::setPosition(position);

    target = position + _orientation;
}
