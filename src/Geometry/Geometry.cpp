#include "Geometry/Geometry.h"

Geometry::Geometry(){}

Geometry::~Geometry(){
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Geometry::load(){
    // Geometry
    if(glIsBuffer(vbo) == GL_TRUE){
        glDeleteBuffers(1, &vbo);
    }

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto sizeOfPositions = positions.size() * sizeof(float);
    auto sizeOfUvs = uvs.size() * sizeof(float);
    auto sizeOfNormals = normals.size() * sizeof(float);

    glBufferData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfUvs + sizeOfNormals, 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfPositions, &positions[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions, sizeOfUvs, &uvs[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfUvs, sizeOfNormals, &normals[0]);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // EBO
    if(glIsBuffer(ebo) == GL_TRUE){
        glDeleteBuffers(1, &ebo);
    }

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    auto sizeOfIndexes = indexes.size() * sizeof(unsigned short);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndexes, &indexes[0], GL_STATIC_DRAW);

    // VAO
    if(glIsVertexArray(vao) == GL_TRUE)
        glDeleteVertexArrays(1, &vao);

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeOfPositions));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeOfPositions + sizeOfUvs));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Don't unbind element buffer before VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Geometry::bindVertexArray(){
    glBindVertexArray(vao);
}
