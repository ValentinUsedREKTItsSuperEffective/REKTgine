#include "Light.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Light::Light(glm::vec3 color, std::string vertexShader, std::string fragmentShader) : Cube(0.1f, vertexShader, fragmentShader), lightColor(color) {}

void Light::load(){
    Cube::load();

    glUseProgram(shader.programID);

    GLuint lightColorLoc = glGetUniformLocation(shader.programID, "lightColor");
    float toFloat3[3] = {lightColor.x, lightColor.y, lightColor.z};
    glUniform3fv(lightColorLoc, 1, toFloat3);

    glUseProgram(0);
}
