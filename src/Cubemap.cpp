#include "Cubemap.hpp"
#include "stb_image.h"

#include <SDL2/SDL_image.h>

#include <iostream>

Cubemap::Cubemap(std::string left, std::string right, std::string top ,std::string bottom, std::string front, std::string back) : skyboxGeometry(2.0), skyboxShader(Shader("Shaders/skybox.vert", "Shaders/skybox.frag")){
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    textures[0] = right;
    textures[1] = left;
    textures[2] = top;
    textures[3] = bottom;
    textures[4] = front;
    textures[5] = back;


    int width, height, nrChannels;
    unsigned char* data;
    for(int i = 0; i < 6; i++){
        data = stbi_load(textures[i].c_str(), &width, &height, &nrChannels, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Cubemap failed to load : " << textures[i] << std::endl;
        }
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glUseProgram(skyboxShader.programID);
    skyboxShader.bindInt("skybox", 0);
}

Cubemap::~Cubemap(){}

void Cubemap::Display(mat4 &projection, mat4 &view){
    glDepthFunc(GL_LEQUAL);

    glUseProgram(skyboxShader.programID);
    skyboxShader.bindMat4("view", glm::mat4(glm::mat3(view)));
    skyboxShader.bindMat4("projection", projection);

    skyboxGeometry.bindVertexArray();
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawElements(GL_TRIANGLES, skyboxGeometry.indexes.size(), GL_UNSIGNED_SHORT, 0);

    glDepthFunc(GL_LESS);
}
