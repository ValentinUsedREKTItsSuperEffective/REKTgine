#include "BaseMaterial.h"

BaseMaterial::BaseMaterial() : color(glm::vec3(1.f, 1.f, 1.f)){
    loadShader();
}
BaseMaterial::BaseMaterial(glm::vec3 color) : color(color) {
    loadShader();
}

BaseMaterial::~BaseMaterial(){}

void BaseMaterial::loadShader(){
    shader = Shader("default.vert", "default.frag");
    shader.load();
}
