#include "BaseMaterial.h"

BaseMaterial::BaseMaterial() : color(glm::vec3(1.f, 1.f, 1.f)){
    colorTexture = Texture();
    colorTexture.load();

    loadShader();
}
BaseMaterial::BaseMaterial(BaseMaterialParameters parameters) : color(parameters.color){
    if(parameters.textureSrc != ""){
        colorTexture = Texture(parameters.textureSrc);
        colorTexture.load();
    }

    loadShader();
}

BaseMaterial::~BaseMaterial(){}

void BaseMaterial::loadShader(){
    shader = Shader("default.vert", "default.frag");
    shader.load();
}
