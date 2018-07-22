#include "Crate.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Crate::Crate(float dim, std::string vertexShader, std::string fragmentShader, std::string textureSrc) : Cube(dim, vertexShader, fragmentShader), _texture(textureSrc),
                                                                                    _sizeTexCoordBytes(sizeof(float)*72)
{
    _texture.load();

    float coordTextureTmp[] = {0, 0,   1, 0,   1, 1,     // Face 1
                           0, 0,   0, 1,   1, 1,     // Face 1

                           0, 0,   1, 0,   1, 1,     // Face 2
                           0, 0,   0, 1,   1, 1,     // Face 2

                           0, 0,   1, 0,   1, 1,     // Face 3
                           0, 0,   0, 1,   1, 1,     // Face 3

                           0, 0,   1, 0,   1, 1,     // Face 4
                           0, 0,   0, 1,   1, 1,     // Face 4

                           0, 0,   1, 0,   1, 1,     // Face 5
                           0, 0,   0, 1,   1, 1,     // Face 5

                           0, 0,   1, 0,   1, 1,     // Face 6
                           0, 0,   0, 1,   1, 1};    // Face 6

    for(int i = 0; i<72; i++)
        _texCoord[i] = coordTextureTmp[i];
}

Crate::~Crate()
{
    //dtor
}

void Crate::load(){
    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1,&_vbo);

    glGenBuffers(1,&_vbo);

    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

    glBufferData(GL_ARRAY_BUFFER,_sizeVerticesBytes+_sizeTexCoordBytes,0,GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER,0,_sizeVerticesBytes,_vertex);
    glBufferSubData(GL_ARRAY_BUFFER,_sizeVerticesBytes,_sizeTexCoordBytes,_texCoord);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Crate::display(glm::mat4 &projection, glm::mat4 &view){
    glm::mat4 modelView = view * matrix;

    // Specify which shader we are using
    glUseProgram(_shader.getProgramID());

        glBindBuffer(GL_ARRAY_BUFFER,_vbo);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(_sizeVerticesBytes));
            glEnableVertexAttribArray(2);

            //Transformations

            // Matrix send to shader as Uniform after transformation
            glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramID(),"modelView"),1,GL_FALSE,glm::value_ptr(modelView));

            glBindTexture(GL_TEXTURE_2D,_texture.getID());

            // Time to draw
            glDrawArrays(GL_TRIANGLES,0,36);

            glBindTexture(GL_TEXTURE_2D,0);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER,0);

    // Don't use the shader anymore
    glUseProgram(0);

}
