#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include <Materials/BaseMaterial.h>
#include <Lights/Light.h>

struct PhongMaterialParameters : public BaseMaterialParameters {

};


class PhongMaterial : public BaseMaterial {
    public:
        PhongMaterial();
        PhongMaterial(PhongMaterialParameters parameters);
        virtual ~PhongMaterial();

        virtual void useLight(Light &light);
        virtual void setViewPosition(glm::vec3 view);

    protected:
        virtual void loadShader() override;
};

#endif // PHONGMATERIAL_H
