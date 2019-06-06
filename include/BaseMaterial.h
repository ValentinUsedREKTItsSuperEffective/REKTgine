#ifndef BASEMATERIAL_H
#define BASEMATERIAL_H

#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

struct BaseMaterialParameters{
    glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
    std::string textureSrc = "";
};

class BaseMaterial{
    public:
        glm::vec3 color;
        Texture colorTexture;

        BaseMaterial();
        BaseMaterial(BaseMaterialParameters parameters);
        virtual ~BaseMaterial();

    protected:
        Shader shader;

        virtual void loadShader();

    private:
};

#endif // BASEMATERIAL_H
