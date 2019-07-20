#include "Cube.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Cube::Cube(float dim, BaseMaterial *mat) : Object3D(), material(mat), vbo(0){
    dim *= 0.5f;

    auto tmpList = std::initializer_list<float>({
        -dim, -dim, -dim,
         dim, -dim, -dim,
         dim,  dim, -dim,
         dim,  dim, -dim,
        -dim,  dim, -dim,
        -dim, -dim, -dim,

        -dim, -dim,  dim,
         dim, -dim,  dim,
         dim,  dim,  dim,
         dim,  dim,  dim,
        -dim,  dim,  dim,
        -dim, -dim,  dim,

        -dim,  dim,  dim,
        -dim,  dim, -dim,
        -dim, -dim, -dim,
        -dim, -dim, -dim,
        -dim, -dim,  dim,
        -dim,  dim,  dim,

         dim,  dim,  dim,
         dim,  dim, -dim,
         dim, -dim, -dim,
         dim, -dim, -dim,
         dim, -dim,  dim,
         dim,  dim,  dim,

        -dim, -dim, -dim,
         dim, -dim, -dim,
         dim, -dim,  dim,
         dim, -dim,  dim,
        -dim, -dim,  dim,
        -dim, -dim, -dim,

        -dim,  dim, -dim,
         dim,  dim, -dim,
         dim,  dim,  dim,
         dim,  dim,  dim,
        -dim,  dim,  dim,
        -dim,  dim, -dim
    });
    std::copy(tmpList.begin(), tmpList.end(), positions);

    tmpList = std::initializer_list<float>({
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,

        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,

        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,

        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f
    });
    std::copy(tmpList.begin(), tmpList.end(), normals);

    tmpList = std::initializer_list<float>({
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    });
    std::copy(tmpList.begin(), tmpList.end(), uvs);

    load();
    material->loadShader();
}

Cube::~Cube(){
    glDeleteBuffers(1, &vbo);
}

void Cube::load(){
    // Geometry
    if(glIsBuffer(vbo) == GL_TRUE){
        glDeleteBuffers(1, &vbo);
    }

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(uvs) + sizeof(normals), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(uvs), uvs);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(uvs), sizeof(normals), normals);

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

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(positions)) + sizeof(uvs));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Cube::display(mat4 &projection, mat4 &view){
    if(material->needUpdate){
        material->update();
        material->needUpdate = false;
    }

    // Bind Textures
    material->bindTextures();

    // Specify which shader we are using
    glUseProgram(material->shader.programID);

    glBindVertexArray(vao);

    //Transformations
    // Matrix send to shader as Uniform after transformation
    material->shader.bindMat4("projection", projection);
    material->shader.bindMat4("view", view);
    material->shader.bindMat4("model", model);

    // Time to draw
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    // Don't use the shader anymore
    glUseProgram(0);
}
