#include "Lights/Light.h"

Light::Light(vec3 color, vec3 amb, vec3 dif, vec3 spec) : Object3D(), ambient(color * amb), diffuse(color * dif), specular(color * spec) {
    lightObservers = {};
}

void Light::setPosition(vec3 position){
    Object3D::setPosition(position);

    notifyAllSubscribers();
}

void Light::addPosition(vec3 position){
    Object3D::addPosition(position);

    notifyAllSubscribers();
}

void Light::rotateAroundPoint(vec3 point, vec3 euler){
    Object3D::rotateAroundPoint(point, euler);

    notifyAllSubscribers();
}

void Light::subscribeProgram(GLuint programID){
    lightObservers.push_back(programID);
}

void Light::notifyAllSubscribers(){
    for(auto programID : lightObservers){
        notifySubscriber(programID);
    }

    glUseProgram(0);
}
