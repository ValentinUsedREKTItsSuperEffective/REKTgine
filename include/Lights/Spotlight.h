#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <Lights/PointLight.h>

class Spotlight : public PointLight{
    public:
        vec3 direction;
        float cutAngle;
        float outAngle;

        Spotlight(float constant, float linear, float quad, vec3 direction, float cutAngle, float outAngle, vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
        virtual ~Spotlight();

        virtual void subscribeProgram(GLuint programID);

    protected:
        virtual void notifySubscriber(GLuint programID);
};

#endif // SPOTLIGHT_H
