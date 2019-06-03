#include "Mesh.h"

#include <cstring>

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Mesh::Mesh(std::string objPath, std::string vertexShader, std::string fragmentShader) : _objLoader(), _shader(vertexShader, fragmentShader),
                                                                                                        _texture(), _vbo(0), _vao(0)
{
    _objLoader.load(objPath, _vertices, _uvs, _normals);
    _sizeVerticesBytes = sizeof(float) * 3 * _vertices.size();
    _sizeUvsBytes = sizeof(float) * 2 * _uvs.size();
    _sizeNormalsBytes = sizeof(float) * 3 * _normals.size();
    _shader.load();
}

Mesh::Mesh(std::string objPath, std::string vertexShader, std::string fragmentShader, std::string textureSrc) : _objLoader(),
                                                                                        _shader(vertexShader, fragmentShader), _texture(textureSrc), _vbo(0), _vao(0)
{
    _objLoader.load(objPath, _vertices, _uvs, _normals);
    _sizeVerticesBytes = sizeof(float) * 3 * _vertices.size();
    _sizeUvsBytes = sizeof(float) * 2 * _uvs.size();
    _sizeNormalsBytes = sizeof(float) * 3 * _normals.size();
    _shader.load();
    _texture.load();
}

Mesh::~Mesh()
{
    glDeleteBuffers(1,&_vbo);
    glDeleteVertexArrays(1,&_vao);
}

void Mesh::display(glm::mat4 &projection, glm::mat4 &modelView)
{
    // Specify which shader we are using
    glUseProgram(_shader.programID);

        glBindVertexArray(_vao);

            //Transformations

            // Matrix send to shader as Uniform after transformation
            glUniformMatrix4fv(glGetUniformLocation(_shader.programID,"projection"),1,GL_FALSE,glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(_shader.programID,"modelView"),1,GL_FALSE,glm::value_ptr(modelView));

            glBindTexture(GL_TEXTURE_2D,_texture.getID());

            // Time to draw
            glDrawArrays(GL_TRIANGLES,0,_vertices.size());

            glBindTexture(GL_TEXTURE_2D,0);

        glBindVertexArray(0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

    // Don't use the shader anymore
    glUseProgram(0);
}

void Mesh::load(){
    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1,&_vbo);

    glGenBuffers(1,&_vbo);

    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

        glBufferData(GL_ARRAY_BUFFER,_sizeVerticesBytes+_sizeUvsBytes+_sizeNormalsBytes,0,GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER,0,_sizeVerticesBytes,_vertices.data());
        glBufferSubData(GL_ARRAY_BUFFER,_sizeVerticesBytes,_sizeUvsBytes,_uvs.data());
        glBufferSubData(GL_ARRAY_BUFFER,_sizeVerticesBytes+_sizeUvsBytes,_sizeNormalsBytes,_normals.data());

    glBindBuffer(GL_ARRAY_BUFFER,0);

    if(glIsVertexArray(_vao) == GL_TRUE)
        glDeleteVertexArrays(1,&_vao);

    glGenVertexArrays(1,&_vao);

    glBindVertexArray(_vao);

        glBindBuffer(GL_ARRAY_BUFFER,_vbo);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(_sizeVerticesBytes));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(_sizeVerticesBytes+_sizeUvsBytes));
            glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);
}

void Mesh::updateVBO(void *data, int sizeBytes, int offset){

    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

        void* address = glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);

        if(address == NULL){
            std::cout << "Error : VBO's mapping" << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            return;
        }

        memcpy((char*)address + offset,data,sizeBytes);

        glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}


void Mesh::useLight(Light &light) {
    glUseProgram(_shader.programID);

        glBindVertexArray(_vao);

            GLuint lightColorLoc = glGetUniformLocation(_shader.programID, "lightColor");
            glm::vec3 lightColor = light.getColor();
            float toFloat3[3] = {lightColor.x, lightColor.y, lightColor.z};
            glUniform3fv(lightColorLoc, 1, toFloat3);

        glBindVertexArray(0);

    glUseProgram(0);
}
