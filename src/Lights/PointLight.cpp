#include "Lights/PointLight.h"

PointLight::PointLight(float constant, float linear, float quad, vec3 col, vec3 amb, vec3 dif, vec3 spec) : Light(col, amb, dif, spec), constant(constant), linear(linear), quadratic(quad){}

PointLight::~PointLight(){}

void PointLight::subscribeProgram(GLuint programID){
    Light::subscribeProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "lights[1].position"), 1, value_ptr(position));

    glUniform3fv(glGetUniformLocation(programID, "lights[1].ambient"), 1, value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(programID, "lights[1].diffuse"), 1, value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(programID, "lights[1].specular"), 1, value_ptr(specular));

    glUniform1f(glGetUniformLocation(programID, "lights[1].constant"), constant);
    glUniform1f(glGetUniformLocation(programID, "lights[1].linear"), linear);
    glUniform1f(glGetUniformLocation(programID, "lights[1].quadratic"), quadratic);
}

void PointLight::notifySubscriber(GLuint programID){
    glUseProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "lights[1].position"), 1, value_ptr(position));
}
