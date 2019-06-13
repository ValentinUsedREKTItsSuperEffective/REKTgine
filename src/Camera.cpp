#include "Camera.h"

#define M_PI 3.14159265358979323846

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 axis) : _theta(0.), _phi(0.), _orientation(), _axis(axis), _sideDisplacement(), _eye(eye), _target(target),
                                                                    _sensibility(0.5f), _speed(0.5f)
{
    setTarget(target);
}

Camera::~Camera()
{
    //dtor
}

void Camera::orientate(int xRel, int yRel){
    _phi += -yRel * _sensibility;
    _theta += -xRel * _sensibility;

    if(_phi > 89.)
        _phi = 89.;
    else if(_phi < -89.)
        _phi = -89.;

    float radPhi = _phi * M_PI / 180;
    float radTheta = _theta * M_PI / 180;

    if(_axis.x == 1.0)
    {
        _orientation.x = sin(radPhi);
        _orientation.y = cos(radPhi) * cos(radTheta);
        _orientation.z = cos(radPhi) * sin(radTheta);
    }
    else if(_axis.y == 1.0)
    {
        _orientation.x = cos(radPhi) * sin(radTheta);
        _orientation.y = sin(radPhi);
        _orientation.z = cos(radPhi) * cos(radTheta);
    }
    else{
        _orientation.x = cos(radPhi) * cos(radTheta);
        _orientation.y = cos(radPhi) * sin(radTheta);
        _orientation.z = sin(radPhi);
    }

    _sideDisplacement = glm::normalize(glm::cross(_axis,_orientation));

    _target = _eye + _orientation;
}

void Camera::translate(Input const &input){
    if(input.inMovement())
        orientate(input.mouseRX, input.mouseRY);

    if(input.getKey(SDL_SCANCODE_UP))
    {
        _eye = _eye + _orientation * _speed;
        _target = _eye + _orientation;
    }
    if(input.getKey(SDL_SCANCODE_DOWN))
    {
        _eye = _eye - _orientation * _speed;
        _target = _eye + _orientation;
    }
    if(input.getKey(SDL_SCANCODE_LEFT))
    {
        _eye = _eye + _sideDisplacement * _speed;
        _target = _eye + _orientation;
    }
    if(input.getKey(SDL_SCANCODE_RIGHT))
    {
        _eye = _eye - _sideDisplacement * _speed;
        _target = _eye + _orientation;
    }
}

void Camera::lookAt(glm::mat4 &modelView){
    modelView = glm::lookAt(_eye,_target,_axis);
}

void Camera::setTarget(glm::vec3 target){
    _orientation = glm::normalize(target - _eye);

    if(_axis.x == 1.0)
    {
        _phi = asin(_orientation.x);
        _theta = acos(_orientation.y / cos(_phi));

        if(_orientation.y < 0)
            _theta *= -1;
    }
    else if(_axis.y == 1.0)
    {
        _phi = asin(_orientation.y);
        _theta = acos(_orientation.z / cos(_phi));

        if(_orientation.z < 0)
            _theta *= -1;
    }
    else{
        _phi = asin(_orientation.z);
        _theta = acos(_orientation.x / cos(_phi));

        if(_orientation.x < 0)
            _theta *= -1;
    }

    _phi = _phi * 180. / M_PI;
    _theta = _theta * 180. / M_PI;
}

void Camera::setPosition(glm::vec3 position){
    _eye = position;
    _target = _eye + _orientation;
}

void Camera::setSensibility(float sensibility){
    _sensibility = sensibility;
}

void Camera::setSpeed(float speed){
    _speed = speed;
}
