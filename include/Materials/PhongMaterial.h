#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include <Materials/BaseMaterial.h>

struct PhongMaterialParameters : public BaseMaterialParameters{

};


class PhongMaterial : public BaseMaterial {
    public:
        PhongMaterial();
        PhongMaterial(PhongMaterialParameters parameters);
        virtual ~PhongMaterial();

    protected:
        virtual void loadShader();
};

#endif // PHONGMATERIAL_H
