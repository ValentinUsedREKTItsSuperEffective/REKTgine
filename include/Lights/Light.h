#ifndef LIGHT_H
#define LIGHT_H

#include "Object3D.h"

class Light : Object3D {
    public:
        glm::vec3 lightColor;
        float intensity;

        Light(glm::vec3 color, float intensity);
};

#endif // LIGHT_H
