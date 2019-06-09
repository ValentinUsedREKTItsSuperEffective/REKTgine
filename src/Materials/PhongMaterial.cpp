#include "Materials/PhongMaterial.h"

PhongMaterial::PhongMaterial() : BaseMaterial() {
    //ctor
}

PhongMaterial::PhongMaterial(PhongMaterialParameters parameters) : BaseMaterial(parameters) {

}

PhongMaterial::~PhongMaterial(){}

void PhongMaterial::loadShader(){
    shader = Shader("Shaders/default.vert", "Shaders/blinnPhong.frag");
    shader.load();
}
