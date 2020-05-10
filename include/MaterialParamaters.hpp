#ifndef MATERIALPARAMATERS_H
#define MATERIALPARAMATERS_H

#include <glm/glm.hpp>

#include <string>


struct MaterialParamaters {
    glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
    std::string textureSrc = "";
    bool inverseImage = true;

    glm::vec3 ambient = glm::vec3(1.f);
    glm::vec3 specular = glm::vec3(1.f);
    std::string specularMapSrc = "";
    float shininess = 32.f;
    std::string emissiveMapSrc = "";
};

#endif // MATERIALPARAMATERS_H
