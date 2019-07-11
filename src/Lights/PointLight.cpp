#include "Lights/PointLight.h"

PointLight::PointLight(float constant, float linear, float quad, vec3 col, vec3 amb, vec3 dif, vec3 spec) : Light(col, amb, dif, spec), constant(constant), linear(linear), quadratic(quad){}

PointLight::~PointLight(){}

void PointLight::subscribeProgram(GLuint programID){
    Light::subscribeProgram(programID);

    glUniform1f(glGetUniformLocation(programID, "pointLight.constant"), constant);
    glUniform1f(glGetUniformLocation(programID, "pointLight.linear"), linear);
    glUniform1f(glGetUniformLocation(programID, "pointLight.quadratic"), quadratic);
}
