#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <Lights/Light.h>

class PointLight : public Light{
    public:
        PointLight(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
        virtual ~PointLight();
};

#endif // POINTLIGHT_H
