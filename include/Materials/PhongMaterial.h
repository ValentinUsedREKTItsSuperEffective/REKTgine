#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include <Materials/BaseMaterial.h>
#include <Light.h>

struct PhongMaterialParameters : public BaseMaterialParameters {

};


class PhongMaterial : public BaseMaterial {
    public:
        PhongMaterial();
        PhongMaterial(PhongMaterialParameters parameters);
        virtual ~PhongMaterial();

        virtual void useLight(Light &light);

    protected:
        virtual void loadShader() override;
};

#endif // PHONGMATERIAL_H
