#include "Materials/PhongMaterial.h"

PhongMaterial::PhongMaterial() : BaseMaterial(), ambient(glm::vec3(1.f)), diffuse(glm::vec3(1.f)), specular(glm::vec3(1.f)), shininess(32.f) {}

PhongMaterial::PhongMaterial(PhongMaterialParameters p) : BaseMaterial(p), ambient(p.ambient), diffuse(p.diffuse), specular(p.specular), shininess(p.shininess) {}

PhongMaterial::~PhongMaterial(){}

void PhongMaterial::loadShader(){
    shader = Shader("Shaders/phong.vert", "Shaders/phong.frag");
    shader.load();
}

void PhongMaterial::update(){
    BaseMaterial::update();

    glUniform3fv(glGetUniformLocation(shader.programID, "material.ambient"), 1, glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(shader.programID, "material.diffuse"), 1, glm::value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(shader.programID, "material.specular"), 1, glm::value_ptr(specular));

    glUniform1f(glGetUniformLocation(shader.programID, "material.shininess"), shininess);
}

// ONLY FOR ONE TYPE OF LIGHT CASTER !
void PhongMaterial::useLight(Light &light){
    glUseProgram(shader.programID);

    float toFloat3[3] = {light.lightColor.x, light.lightColor.y, light.lightColor.z};
    glUniform3fv(glGetUniformLocation(shader.programID, "light.color"), 1, toFloat3);

    glUniform3fv(glGetUniformLocation(shader.programID, "light.ambient"), 1, glm::value_ptr(light.ambient));

    glUseProgram(0);

    light.subscribeProgram(shader.programID);
}
