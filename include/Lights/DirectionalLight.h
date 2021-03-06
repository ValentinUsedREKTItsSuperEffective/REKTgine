#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <Lights/Light.h>

class DirectionalLight : public Light{
    public:
        glm::vec3 direction;

        DirectionalLight(vec3 direction, vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
        virtual ~DirectionalLight();

        virtual void subscribeProgram(GLuint programID);

    protected:
        virtual void notifySubscriber(GLuint programID);
};

#endif // DIRECTIONALLIGHT_H
