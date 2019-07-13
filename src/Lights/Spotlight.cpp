#include "Lights/Spotlight.h"

Spotlight::Spotlight(float constant, float linear, float quad, vec3 dir, float angle, vec3 col, vec3 amb, vec3 dif, vec3 spec) : PointLight(constant, linear, quad, col, amb, dif, spec), direction(dir), angle(angle){}

Spotlight::~Spotlight(){}

void Spotlight::subscribeProgram(GLuint programID){
    PointLight::subscribeProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "spotlight.direction"), 1, value_ptr(direction));
    glUniform1f(glGetUniformLocation(programID, "spotlight.cutAngle"), cos(angle));
}
