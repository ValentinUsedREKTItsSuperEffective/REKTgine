#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <Lights/Light.h>

class Spotlight : public Light{
    public:
        Spotlight(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
        virtual ~Spotlight();
};

#endif // SPOTLIGHT_H
