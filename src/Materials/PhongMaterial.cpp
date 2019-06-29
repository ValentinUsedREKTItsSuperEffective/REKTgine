#include "Materials/PhongMaterial.h"

PhongMaterial::PhongMaterial() : BaseMaterial(), ambient(glm::vec3(1.f)), specular(glm::vec3(1.f)), shininess(32.f) {
    specularMap = Texture();
    specularMap.load();
}

PhongMaterial::PhongMaterial(PhongMaterialParameters p) : BaseMaterial(p), specular(p.specular), shininess(p.shininess) {
    if(p.ambient == glm::vec3(1.f)){
        ambient = p.color;
    } else {
        ambient = p.ambient;
    }

    if(p.specularMapSrc != ""){
        specularMap = Texture(p.specularMapSrc);
    } else {
        specularMap = Texture();
    }
    specularMap.load();
}

PhongMaterial::~PhongMaterial(){}

void PhongMaterial::loadShader(){
    shader = Shader("Shaders/phong.vert", "Shaders/phong.frag");
    shader.load();
}

void PhongMaterial::update(){
    BaseMaterial::update();

    glUniform3fv(glGetUniformLocation(shader.programID, "material.ambient"), 1, glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(shader.programID, "material.specular"), 1, glm::value_ptr(specular));
    glUniform1i(glGetUniformLocation(shader.programID, "material.specularMap"), 1);
    glUniform1f(glGetUniformLocation(shader.programID, "material.shininess"), shininess);
}

void PhongMaterial::bindTextures(){
    BaseMaterial::bindTextures();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap.textureID);
}

// ONLY FOR ONE TYPE OF LIGHT CASTER !
void PhongMaterial::useLight(Light &light){
    glUseProgram(shader.programID);

    glUniform3fv(glGetUniformLocation(shader.programID, "light.ambient"), 1, glm::value_ptr(light.ambient));
    glUniform3fv(glGetUniformLocation(shader.programID, "light.diffuse"), 1, glm::value_ptr(light.diffuse));
    glUniform3fv(glGetUniformLocation(shader.programID, "light.specular"), 1, glm::value_ptr(light.specular));

    glUseProgram(0);

    light.subscribeProgram(shader.programID);
}
