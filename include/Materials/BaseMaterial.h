#ifndef BASEMATERIAL_H
#define BASEMATERIAL_H

#include <glm/glm.hpp>

#include "MaterialParamaters.hpp"
#include "Shader.h"
#include "Texture.h"
#include "Lights/Light.h"

class BaseMaterial{
    public:
        glm::vec3 color;
        Texture colorTexture;
        bool needUpdate;

        Shader shader;

        BaseMaterial();
        BaseMaterial(MaterialParamaters parameters);
        virtual ~BaseMaterial();
        virtual void update();
        virtual void bindTextures();
        virtual void loadShader();

        virtual void useLight(Light &light);

    protected:

    private:
};

#endif // BASEMATERIAL_H
