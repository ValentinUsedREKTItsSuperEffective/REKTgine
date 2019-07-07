#include "Lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 dir, vec3 col, vec3 amb, vec3 dif, vec3 spec) : Light(col, amb, dif, spec), direction(dir){}

DirectionalLight::~DirectionalLight(){}

void DirectionalLight::subscribeProgram(GLuint programID){
    Light::subscribeProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "directionalLight.direction"), 1, glm::value_ptr(direction));
}
