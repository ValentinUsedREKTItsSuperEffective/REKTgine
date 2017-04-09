#include "Cube.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Cube::Cube(float dim, std::string vertexShader, std::string fragmentShader) : _shader(vertexShader,fragmentShader), _vbo(0), _sizeVerticesBytes(sizeof(float)*108),
                                                                    _sizeColorBytes(sizeof(float)*108){

    _shader.load();

    dim /= 2.f;

    float vertexTmp[] = {-dim, -dim, -dim,   dim, -dim, -dim,   dim, dim, -dim,
                       -dim, -dim, -dim,   -dim, dim, -dim,   dim, dim, -dim,
                       dim, -dim, dim,   dim, -dim, -dim,   dim, dim, -dim,
                       dim, -dim, dim,   dim, dim, dim,   dim, dim, -dim,
                       -dim, -dim, dim,   dim, -dim, dim,   dim, -dim, -dim,
                       -dim, -dim, dim,   -dim, -dim, -dim,   dim, -dim, -dim,
                       -dim, -dim, dim,   dim, -dim, dim,   dim, dim, dim,
                       -dim, -dim, dim,   -dim, dim, dim,   dim, dim, dim,
                       -dim, -dim, -dim,   -dim, -dim, dim,   -dim, dim, dim,
                       -dim, -dim, -dim,   -dim, dim, -dim,   -dim, dim, dim,
                       -dim, dim, dim,   dim, dim, dim,   dim, dim, -dim,
                       -dim, dim, dim,   -dim, dim, -dim,   dim, dim, -dim};

    float colorTmp[] = {1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0};

    for(int i = 0; i<108; i++){
        _vertex[i] = vertexTmp[i];
        _color[i] = colorTmp[i];
    }
}

Cube::~Cube()
{
    glDeleteBuffers(1,&_vbo);
}

void Cube::display(glm::mat4 &projection, glm::mat4 &modelView){

    // Specify which shader we are using
    glUseProgram(_shader.getProgramID());

        glBindBuffer(GL_ARRAY_BUFFER,_vbo);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(_sizeVerticesBytes));
            glEnableVertexAttribArray(1);

            //Transformations

            // Matrix send to shader as Uniform after transformation
            glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramID(),"modelView"),1,GL_FALSE,glm::value_ptr(modelView));

            // Time to draw
            glDrawArrays(GL_TRIANGLES,0,36);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER,0);

    // Don't use the shader anymore
    glUseProgram(0);
}

void Cube::load(){

    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1,&_vbo);

    glGenBuffers(1,&_vbo);

    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

    glBufferData(GL_ARRAY_BUFFER,_sizeVerticesBytes+_sizeVerticesBytes,0,GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER,0,_sizeVerticesBytes,_vertex);
    glBufferSubData(GL_ARRAY_BUFFER,_sizeVerticesBytes,_sizeColorBytes  ,_color);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}
