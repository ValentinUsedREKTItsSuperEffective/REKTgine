#include "Lights/PointLight.h"

PointLight::PointLight(float constant, float linear, float quad, vec3 col, vec3 amb, vec3 dif, vec3 spec) : Light(col, amb, dif, spec), constant(constant), linear(linear), quadratic(quad){}

PointLight::~PointLight(){}

void PointLight::subscribeProgram(GLuint programID){
    Light::subscribeProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "pointLight.position"), 1, value_ptr(position));

    glUniform3fv(glGetUniformLocation(programID, "pointLight.ambient"), 1, value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(programID, "pointLight.diffuse"), 1, value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(programID, "pointLight.specular"), 1, value_ptr(specular));

    glUniform1f(glGetUniformLocation(programID, "pointLight.constant"), constant);
    glUniform1f(glGetUniformLocation(programID, "pointLight.linear"), linear);
    glUniform1f(glGetUniformLocation(programID, "pointLight.quadratic"), quadratic);
}

void PointLight::notifySubscriber(GLuint programID){
    glUseProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "pointLight.position"), 1, value_ptr(position));
}
