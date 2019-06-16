#include "Camera.h"

#define M_PI        3.1415926535897932384626433832795
#define M_PI_89     1.5533430342749533234620847839549
#define M_PI_180    0.0174532925199432957692369076848

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up) : Object3D(), _orientation(), _axis(up), sensibility(0.5f), speed(0.5f){
    Object3D::setPosition(position);

    setTarget(target);
}

Camera::~Camera(){}

void Camera::orientate(int xRel, int yRel){
    rotation.x += (-yRel * sensibility) * M_PI_180;
    rotation.y += (-xRel * sensibility) * M_PI_180;

    if(rotation.x > M_PI_89){
        rotation.x = M_PI_89;
    } else if(rotation.x < -M_PI_89){
        rotation.x = -M_PI_89;
    }

    if(_axis.x == 1.0){
        _orientation.x = sin(rotation.x);
        _orientation.y = cos(rotation.x) * cos(rotation.y);
        _orientation.z = cos(rotation.x) * sin(rotation.y);
    } else if(_axis.y == 1.0){
        _orientation.x = cos(rotation.x) * sin(rotation.y);
        _orientation.y = sin(rotation.x);
        _orientation.z = cos(rotation.x) * cos(rotation.y);
    } else {
        _orientation.x = cos(rotation.x) * cos(rotation.y);
        _orientation.y = cos(rotation.x) * sin(rotation.y);
        _orientation.z = sin(rotation.x);
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
        rotation.x = asin(_orientation.x);
        rotation.y = acos(_orientation.y / cos(rotation.x));

        if(_orientation.y < 0)
            rotation.y *= -1;
    } else if(_axis.y == 1.0){
        rotation.x = asin(_orientation.y);
        rotation.y = acos(_orientation.z / cos(rotation.x));

        if(_orientation.z < 0)
            rotation.y *= -1;
    } else {
        rotation.x = asin(_orientation.z);
        rotation.y = acos(_orientation.x / cos(rotation.x));

        if(_orientation.x < 0)
            rotation.y *= -1;
    }
}

void Camera::setPosition(glm::vec3 position){
    Object3D::setPosition(position);

    target = position + _orientation;
}
