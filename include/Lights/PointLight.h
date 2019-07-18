#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <Lights/Light.h>

class PointLight : public Light{
    public:
        float constant;
        float linear;
        float quadratic;

        PointLight(float constant, float linear, float quadratic, vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
        virtual ~PointLight();

        virtual void subscribeProgram(GLuint programID);

    protected:
        virtual void notifySubscriber(GLuint programID);
};

#endif // POINTLIGHT_H
