#include "Materials/PhongMaterial.h"

PhongMaterial::PhongMaterial() : BaseMaterial(), ambient(glm::vec3(1.f)), specular(glm::vec3(1.f)), shininess(32.f) {
    specularMap = Texture();
    specularMap.load();

    emissiveMap = Texture();
    emissiveMap.load();
}

PhongMaterial::PhongMaterial(MaterialParamaters p) : BaseMaterial(p), specular(p.specular), shininess(p.shininess) {
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
    specularMap.inverseImage = p.inverseImage;
    specularMap.load();

    if(p.emissiveMapSrc != ""){
        emissiveMap = Texture(p.emissiveMapSrc);
    } else {
        emissiveMap = Texture();
        emissiveMap.colorByDefault = glm::vec3();
    }
    emissiveMap.inverseImage = p.inverseImage;
    emissiveMap.load();
}

PhongMaterial::~PhongMaterial(){}

void PhongMaterial::loadShader(){
    shader = Shader("Shaders/phong.vert", "Shaders/phong.frag");
    shader.load();
}

void PhongMaterial::update(){
    BaseMaterial::update();

    shader.bindFloat3("material.ambient", ambient);
    shader.bindFloat3("material.specular", specular);
    shader.bindInt("material.specularMap", 1);
    shader.bindFloat("material.shininess", shininess);
    shader.bindInt("material.emissiveMap", 2);
}

void PhongMaterial::bindTextures(){
    BaseMaterial::bindTextures();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap.textureID);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, emissiveMap.textureID);
}

void PhongMaterial::useLight(Light &light){
    glUseProgram(shader.programID);

    light.subscribeProgram(shader.programID);

    glUseProgram(0);
}

void PhongMaterial::setViewPosition(glm::vec3 view){
    glUseProgram(shader.programID);

    shader.bindFloat3("cameraPosition", view);

    glUseProgram(0);
}
