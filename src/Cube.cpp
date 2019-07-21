#include "Cube.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Cube::Cube(Geometry *geom, BaseMaterial *mat) : Object3D(), geometry(geom), material(mat){
    material->loadShader();
}

Cube::~Cube(){}

void Cube::display(mat4 &projection, mat4 &view){
    if(material->needUpdate){
        material->update();
        material->needUpdate = false;
    }

    // Bind Textures
    material->bindTextures();

    // Specify which shader we are using
    glUseProgram(material->shader.programID);

    geometry->bindVertexArray();

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
