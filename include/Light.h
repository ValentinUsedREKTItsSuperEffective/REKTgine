#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light {
    public:
        glm::vec3 lightColor;

        Light(glm::vec3 color);
};

#endif // LIGHT_H
