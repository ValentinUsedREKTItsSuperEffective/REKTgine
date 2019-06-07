#include "Light.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Light::Light(glm::vec3 color, std::string vertexShader, std::string fragmentShader) : Cube(0.1f, vertexShader, fragmentShader), lightColor(color) {}

void Light::load(){
    Cube::load();

    if(glIsVertexArray(_lightVAO) == GL_TRUE)
        glDeleteVertexArrays(1,&_lightVAO);

    glGenVertexArrays(1,&_lightVAO);

    glUseProgram(shader.programID);

    glBindVertexArray(_lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            GLuint lightColorLoc = glGetUniformLocation(shader.programID, "lightColor");
            float toFloat3[3] = {lightColor.x, lightColor.y, lightColor.z};
            glUniform3fv(lightColorLoc, 1, toFloat3);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glUseProgram(0);
}

void Light::display(glm::mat4 &projection, glm::mat4 &modelView) {
    // Specify which shader we are using
    glUseProgram(shader.programID);

        glBindVertexArray(_lightVAO);

            //Transformations

            // Matrix send to shader as Uniform after transformation
            glUniformMatrix4fv(glGetUniformLocation(shader.programID,"projection"),1,GL_FALSE,glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shader.programID,"modelView"),1,GL_FALSE,glm::value_ptr(modelView));

            // Time to draw
            glDrawArrays(GL_TRIANGLES,0,36);

        glBindVertexArray(0);

        glDisableVertexAttribArray(0);

    // Don't use the shader anymore
    glUseProgram(0);
}
