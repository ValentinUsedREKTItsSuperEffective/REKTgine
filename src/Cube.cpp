#include "Cube.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Cube::Cube(float dim, BaseMaterial *mat) : Object3D(), material(mat), vbo(0){
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
    material->loadShader();
}

Cube::~Cube(){
    glDeleteBuffers(1, &vbo);
}

void Cube::load(){
    // Geometry
    if(glIsBuffer(vbo) == GL_TRUE)
        glDeleteBuffers(1, &vbo);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(uvs), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(uvs), uvs);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // VAO
    if(glIsVertexArray(vao) == GL_TRUE)
        glDeleteVertexArrays(1, &vao);

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(positions)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Cube::display(glm::mat4 &projection, glm::mat4 &view){
    if(material->needUpdate){
        material->update();
    }

    // Bind Textures
    material->bindTextures();

    // Specify which shader we are using
    glUseProgram(material->shader.programID);

    glBindVertexArray(vao);

    //Transformations
    // Matrix send to shader as Uniform after transformation
    glUniformMatrix4fv(glGetUniformLocation(material->shader.programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(material->shader.programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(material->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

    // Time to draw
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    // Don't use the shader anymore
    glUseProgram(0);
}
