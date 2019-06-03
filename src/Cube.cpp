#include "Cube.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Cube::Cube(float dim, std::string vertexShader, std::string fragmentShader) : Object3D(), shader(vertexShader,fragmentShader), vbo(0){

    shader.load();

    dim /= 2.f;

    float positionsTmp[] = {
        -dim, -dim, -dim,   dim, -dim, -dim,   dim, dim, -dim,
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
        -dim, dim, dim,   -dim, dim, -dim,   dim, dim, -dim
    };

    for(int i = 0; i<108; i++){
        positions[i] = positionsTmp[i];
    }

    float uvsTmp[] = {
        0, 0,   1, 0,   1, 1,     // Face 1
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
        0, 0,   0, 1,   1, 1      // Face 6
    };

    for(int i = 0; i<72; i++){
        uvs[i] = uvsTmp[i];
    }

    load();
}

Cube::~Cube(){
    glDeleteBuffers(1, &vbo);
}

void Cube::load(){
    if(glIsBuffer(vbo) == GL_TRUE)
        glDeleteBuffers(1, &vbo);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(uvs), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(uvs), uvs);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::display(glm::mat4 &projection, glm::mat4 &modelView){

    // Specify which shader we are using
    glUseProgram(shader.programID);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            //Transformations

            // Matrix send to shader as Uniform after transformation
            glUniformMatrix4fv(glGetUniformLocation(shader.programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shader.programID, "modelView"), 1, GL_FALSE, glm::value_ptr(modelView));

            // Time to draw
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glDisableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Don't use the shader anymore
    glUseProgram(0);
}
