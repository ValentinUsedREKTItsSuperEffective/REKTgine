#include "Camera.h"

#define M_PI        3.1415926535897932384626433832795
#define M_PI_89     1.5533430342749533234620847839549
#define M_PI_180    0.0174532925199432957692369076848

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up) : Object3D(), forwardVector(glm::vec3()), _axis(up), sensibility(0.5f), speed(0.5f){
    setPosition(position);

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
        forwardVector.x = sin(rotation.x);
        forwardVector.y = cos(rotation.x) * cos(rotation.y);
        forwardVector.z = cos(rotation.x) * sin(rotation.y);
    } else if(_axis.y == 1.0){
        forwardVector.x = cos(rotation.x) * sin(rotation.y);
        forwardVector.y = sin(rotation.x);
        forwardVector.z = cos(rotation.x) * cos(rotation.y);
    } else {
        forwardVector.x = cos(rotation.x) * cos(rotation.y);
        forwardVector.y = cos(rotation.x) * sin(rotation.y);
        forwardVector.z = sin(rotation.x);
    }

    sideDisplacement = glm::normalize(glm::cross(_axis, forwardVector));
}

void Camera::translate(Input const &input){
    if(input.inMovement()){
        orientate(input.mouseRX, input.mouseRY);
    }

    if(input.getKey(SDL_SCANCODE_UP)){
        setPosition(position + forwardVector * speed);
    }

    if(input.getKey(SDL_SCANCODE_DOWN)){
        setPosition(position - forwardVector * speed);
    }

    if(input.getKey(SDL_SCANCODE_LEFT)){
        setPosition(position + sideDisplacement * speed);
    }

    if(input.getKey(SDL_SCANCODE_RIGHT)){
        setPosition(position - sideDisplacement * speed);
    }
}

void Camera::lookAt(glm::mat4 &view){
    view = glm::lookAt(position, position + forwardVector, _axis);
}

void Camera::setTarget(glm::vec3 target){
    forwardVector = glm::normalize(target - position);

    if(_axis.x == 1.0){
        rotation.x = asin(forwardVector.x);
        rotation.y = acos(forwardVector.y / cos(rotation.x));

        if(forwardVector.y < 0)
            rotation.y *= -1;
    } else if(_axis.y == 1.0){
        rotation.x = asin(forwardVector.y);
        rotation.y = acos(forwardVector.z / cos(rotation.x));

        if(forwardVector.z < 0)
            rotation.y *= -1;
    } else {
        rotation.x = asin(forwardVector.z);
        rotation.y = acos(forwardVector.x / cos(rotation.x));

        if(forwardVector.x < 0)
            rotation.y *= -1;
    }
}
