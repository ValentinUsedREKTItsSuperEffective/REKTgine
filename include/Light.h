#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Cube.h"

class Light : public Cube {
    public:
        glm::vec3 lightColor;

        Light(glm::vec3 color, std::string vertexShader, std::string fragmentShader);
        virtual void load() override;
};

#endif // LIGHT_H
