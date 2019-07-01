#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <Lights/Light.h>

class DirectionalLight : public Light{
    public:
        DirectionalLight(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
        virtual ~DirectionalLight();
};

#endif // DIRECTIONALLIGHT_H
