#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include <Materials/BaseMaterial.hpp>
#include <Lights/Light.h>

class PhongMaterial : public BaseMaterial {
    public:
        glm::vec3 ambient;
        glm::vec3 specular;
        Texture specularMap;
        float shininess;
        Texture emissiveMap;

        PhongMaterial();
        PhongMaterial(MaterialParamaters parameters);
        virtual ~PhongMaterial();
        virtual void update();
        virtual void bindTextures();

        virtual void useLight(Light &light);
        virtual void setViewPosition(glm::vec3 view);

    protected:
        virtual void loadShader() override;
};

#endif // PHONGMATERIAL_H
