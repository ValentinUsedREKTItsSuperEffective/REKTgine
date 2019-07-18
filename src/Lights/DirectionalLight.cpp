#include "Lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 dir, vec3 col, vec3 amb, vec3 dif, vec3 spec) : Light(col, amb, dif, spec), direction(dir){}

DirectionalLight::~DirectionalLight(){}

void DirectionalLight::subscribeProgram(GLuint programID){
    Light::subscribeProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "directionalLight.direction"), 1, glm::value_ptr(direction));

    glUniform3fv(glGetUniformLocation(programID, "directionalLight.ambient"), 1, value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(programID, "directionalLight.diffuse"), 1, value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(programID, "directionalLight.specular"), 1, value_ptr(specular));
}
