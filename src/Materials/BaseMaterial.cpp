#include "Materials/BaseMaterial.h"

BaseMaterial::BaseMaterial() : color(glm::vec3(1.f, 1.f, 1.f)), needUpdate(true){
    colorTexture = Texture();
    colorTexture.load();
}
BaseMaterial::BaseMaterial(MaterialParamaters parameters) : color(parameters.color), needUpdate(true){
    if(parameters.textureSrc != ""){
        colorTexture = Texture(parameters.textureSrc);
    } else {
        colorTexture = Texture();
    }
    colorTexture.inverseImage = parameters.inverseImage;
    colorTexture.load();
}

BaseMaterial::~BaseMaterial(){}

void BaseMaterial::loadShader(){
    shader = Shader("Shaders/default.vert", "Shaders/default.frag");
    shader.load();
}

void BaseMaterial::update(){
    glUseProgram(shader.programID);

    shader.bindFloat3("material.color", color);
    shader.bindInt("material.map", 0);
}

void BaseMaterial::bindTextures(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorTexture.textureID);
}

void BaseMaterial::useLight(Light &light){}
