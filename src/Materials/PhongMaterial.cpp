#include "Materials/PhongMaterial.h"

PhongMaterial::PhongMaterial() : BaseMaterial(), ambient(glm::vec3(1.f)), specular(glm::vec3(1.f)), shininess(32.f) {
    specularMap = Texture();
    specularMap.load();

    emissiveMap = Texture();
    emissiveMap.load();
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

    if(p.emissiveMapSrc != ""){
        emissiveMap = Texture(p.emissiveMapSrc);
    } else {
        emissiveMap = Texture();
        emissiveMap.colorByDefault = glm::vec3();
    }
    emissiveMap.load();
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
    glUniform1i(glGetUniformLocation(shader.programID, "material.emissiveMap"), 2);
}

void PhongMaterial::bindTextures(){
    BaseMaterial::bindTextures();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap.textureID);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, emissiveMap.textureID);
}

// ONLY FOR ONE TYPE OF LIGHT CASTER !
// TODO : Move to light. Same than subscribeProgram.
void PhongMaterial::useLight(Light &light){
    glUseProgram(shader.programID);

    light.subscribeProgram(shader.programID);

    glUseProgram(0);
}

void PhongMaterial::setViewPosition(glm::vec3 view){
    glUseProgram(shader.programID);

    float viewPosition[3] = {view.x, view.y, view.z};
    glUniform3fv(glGetUniformLocation(shader.programID, "cameraPosition"), 1, viewPosition);

    glUseProgram(0);
}
