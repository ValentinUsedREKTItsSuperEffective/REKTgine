#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include <Materials/BaseMaterial.h>
#include <Lights/Light.h>

struct PhongMaterialParameters : public BaseMaterialParameters {
    glm::vec3 ambient = glm::vec3(1.f);
    glm::vec3 specular = glm::vec3(1.f);
    std::string specularMapSrc = "";
    float shininess = 32.f;
};

class PhongMaterial : public BaseMaterial {
    public:
        glm::vec3 ambient;
        glm::vec3 specular;
        Texture specularMap;
        float shininess;

        PhongMaterial();
        PhongMaterial(PhongMaterialParameters parameters);
        virtual ~PhongMaterial();
        virtual void update();
        virtual void bindTextures();

        virtual void useLight(Light &light);

    protected:
        virtual void loadShader() override;
};

#endif // PHONGMATERIAL_H
