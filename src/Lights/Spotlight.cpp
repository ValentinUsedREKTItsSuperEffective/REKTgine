#include "Lights/Spotlight.h"

Spotlight::Spotlight(float constant, float linear, float quad, vec3 dir, float cutAngle, float outAngle, vec3 col, vec3 amb, vec3 dif, vec3 spec) : PointLight(constant, linear, quad, col, amb, dif, spec), direction(dir), cutAngle(cutAngle), outAngle(outAngle){}

Spotlight::~Spotlight(){}

void Spotlight::subscribeProgram(GLuint programID){
    PointLight::subscribeProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "lights[2].position"), 1, value_ptr(position));

    glUniform3fv(glGetUniformLocation(programID, "lights[2].ambient"), 1, value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(programID, "lights[2].diffuse"), 1, value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(programID, "lights[2].specular"), 1, value_ptr(specular));

    glUniform3fv(glGetUniformLocation(programID, "lights[2].direction"), 1, value_ptr(direction));
    glUniform1f(glGetUniformLocation(programID, "lights[2].cutAngle"), cos(cutAngle));
    glUniform1f(glGetUniformLocation(programID, "lights[2].outAngle"), cos(outAngle));

    glUniform1f(glGetUniformLocation(programID, "lights[2].constant"), constant);
    glUniform1f(glGetUniformLocation(programID, "lights[2].linear"), linear);
    glUniform1f(glGetUniformLocation(programID, "lights[2].quadratic"), quadratic);
}

void Spotlight::notifySubscriber(GLuint programID){
    glUseProgram(programID);

    glUniform3fv(glGetUniformLocation(programID, "lights[2].position"), 1, value_ptr(position));
}
