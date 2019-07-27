#include "Camera.h"

#define M_PI        3.1415926535897932384626433832795
#define M_PI_89     1.5533430342749533234620847839549
#define M_PI_180    0.0174532925199432957692369076848

Camera::Camera(vec3 position, vec3 target, double fov, double aspect, double near, double far) : Object3D(), projectionMatrix(perspective(fov, aspect, near, far)), sensibility(0.5f), speed(0.25f), direction(vec3()), right(vec3()), up(vec3()), worldUp(vec3(0.0, 1.0, 0.0)){
    setPosition(position);

    direction = normalize(target - position);

    rotation.x = asin(direction.y);
    rotation.y = acos(direction.z / cos(rotation.x));

    if(direction.z < 0)
        rotation.y *= -1;

    right = normalize(cross(direction, worldUp));
    up = normalize(cross(right, direction));
}

Camera::~Camera(){}

void Camera::orientate(int xRel, int yRel){
    addRotationFromEuler(vec3((-yRel * sensibility) * M_PI_180, (-xRel * sensibility) * M_PI_180, 0.0));

    if(rotation.x > M_PI_89){
        rotation.x = M_PI_89;
    } else if(rotation.x < -M_PI_89){
        rotation.x = -M_PI_89;
    }

    direction.x = cos(rotation.x) * sin(rotation.y);
    direction.y = sin(rotation.x);
    direction.z = cos(rotation.x) * cos(rotation.y);

    right = normalize(cross(direction, worldUp));
    up = normalize(cross(right, direction));
}

void Camera::translate(Input const &input){
    if(input.inMovement()){
        orientate(input.mouseRX, input.mouseRY);
    }

    if(input.getKey(SDL_SCANCODE_UP)){
        addPosition(direction * speed);
    }

    if(input.getKey(SDL_SCANCODE_DOWN)){
        addPosition(-direction * speed);
    }

    if(input.getKey(SDL_SCANCODE_LEFT)){
        addPosition(-right * speed);
    }

    if(input.getKey(SDL_SCANCODE_RIGHT)){
        addPosition(right * speed);
    }
}

mat4 Camera::getViewMatrix(){
    return lookAt(position, position + direction, up);
}
