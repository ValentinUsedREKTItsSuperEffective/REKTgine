#include "Materials/BaseMaterial.h"

BaseMaterial::BaseMaterial() : color(glm::vec3(1.f, 1.f, 1.f)), needUpdate(true){
    colorTexture = Texture();
    colorTexture.load();
}
BaseMaterial::BaseMaterial(BaseMaterialParameters parameters) : color(parameters.color), needUpdate(true){
    if(parameters.textureSrc != ""){
        colorTexture = Texture(parameters.textureSrc);
    } else {
        colorTexture = Texture();
    }
    colorTexture.load();
}

BaseMaterial::~BaseMaterial(){}

void BaseMaterial::loadShader(){
    shader = Shader("Shaders/default.vert", "Shaders/default.frag");
    shader.load();
}

void BaseMaterial::update(){
    glUseProgram(shader.programID);

    glUniform3fv(glGetUniformLocation(shader.programID, "material.color"), 1, glm::value_ptr(color));

    glUniform1i(glGetUniformLocation(shader.programID, "material.map"), 0);
}

void BaseMaterial::bindTextures(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorTexture.textureID);
}

void BaseMaterial::useLight(Light &light){}
