#include "Materials/BaseMaterial.h"

BaseMaterial::BaseMaterial() : color(glm::vec3(1.f, 1.f, 1.f)), needUpdate(true){
    colorTexture = Texture();
    colorTexture.load();

    loadShader();
}
BaseMaterial::BaseMaterial(BaseMaterialParameters parameters) : color(parameters.color), needUpdate(true){
    if(parameters.textureSrc != ""){
        colorTexture = Texture(parameters.textureSrc);
        colorTexture.load();
    }

    loadShader();
}

BaseMaterial::~BaseMaterial(){}

void BaseMaterial::loadShader(){
    shader = Shader("Shaders/default.vert", "Shaders/default.frag");
    shader.load();
}

void BaseMaterial::update(){
    glUseProgram(shader.programID);

    GLuint colorLoc = glGetUniformLocation(shader.programID, "color");
    float toFloat3[3] = {color.x, color.y, color.z};
    glUniform3fv(colorLoc, 1, toFloat3);

    glUniform1i(glGetUniformLocation(shader.programID, "colorTex"), 0);

    glUseProgram(0);

    needUpdate = false;
}

void BaseMaterial::bindTextures(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorTexture.textureID);
}

void BaseMaterial::useLight(Light &light){}
