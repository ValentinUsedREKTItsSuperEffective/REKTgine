#include "Lights/Light.h"

Light::Light(glm::vec3 color, glm::vec3 amb, glm::vec3 dif) : Object3D(), color(color), ambient(amb), diffuse(dif) {
    lightObservers = {};
}

void Light::setPosition(glm::vec3 position){
    Object3D::setPosition(position);

    notifyAllSubscribers();
}

void Light::addPosition(glm::vec3 position){
    Object3D::addPosition(position);

    notifyAllSubscribers();
}

void Light::rotateAroundPoint(glm::vec3 point, glm::vec3 euler){
    Object3D::rotateAroundPoint(point, euler);

    notifyAllSubscribers();
}

void Light::subscribeProgram(GLuint programID){
    lightObservers.push_back(programID);

    notifySubscriber(programID);

    glUseProgram(0);
}

void Light::notifySubscriber(GLuint programID){
    glUseProgram(programID);

    float ligthPosition[3] = {position.x, position.y, position.z};
    glUniform3fv(glGetUniformLocation(programID, "vLightPosition"), 1, ligthPosition);
}

void Light::notifyAllSubscribers(){
    for(auto programID : lightObservers){
        notifySubscriber(programID);
    }

    glUseProgram(0);
}
