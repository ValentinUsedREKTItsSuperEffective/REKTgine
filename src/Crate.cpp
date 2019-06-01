#include "Crate.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Crate::Crate(float dim, std::string vertexShader, std::string fragmentShader, std::string textureSrc) : Cube(dim, vertexShader, fragmentShader), _texture(textureSrc)
{
    _texture.load();
}

Crate::~Crate()
{
    //dtor
}

void Crate::display(glm::mat4 &projection, glm::mat4 &view){
    glm::mat4 modelView = view * matrix;

    // Specify which shader we are using
    glUseProgram(shader.getProgramID());

        glBindBuffer(GL_ARRAY_BUFFER,vbo);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(sizeof(positions)));
            glEnableVertexAttribArray(1);

            //Transformations

            // Matrix send to shader as Uniform after transformation
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(),"modelView"),1,GL_FALSE,glm::value_ptr(modelView));

            glBindTexture(GL_TEXTURE_2D,_texture.getID());

            // Time to draw
            glDrawArrays(GL_TRIANGLES,0,36);

            glBindTexture(GL_TEXTURE_2D,0);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER,0);

    // Don't use the shader anymore
    glUseProgram(0);

}
