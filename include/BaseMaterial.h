#ifndef BASEMATERIAL_H
#define BASEMATERIAL_H

#include <glm/glm.hpp>

#include "Shader.h"

class BaseMaterial{
    public:
        glm::vec3 color;

        BaseMaterial();
        BaseMaterial(glm::vec3 color);
        virtual ~BaseMaterial();

    protected:
        Shader shader;

        virtual void loadShader();

    private:
};

#endif // BASEMATERIAL_H
