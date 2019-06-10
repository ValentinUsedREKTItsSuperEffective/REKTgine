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

// ONLY FOR ONE TYPE OF LIGHT CASTER !
void PhongMaterial::useLight(Light &light){
    glUseProgram(shader.programID);

    float toFloat3[3] = {light.lightColor.x, light.lightColor.y, light.lightColor.z};
    glUniform3fv(glGetUniformLocation(shader.programID, "ambientColor"), 1, toFloat3);

    glUniform1f(glGetUniformLocation(shader.programID, "ambientIntensity"), light.intensity);

    glUseProgram(0);
}
