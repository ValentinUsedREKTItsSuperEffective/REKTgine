#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <Lights/PointLight.h>

class Spotlight : public PointLight{
    public:
        vec3 direction;
        float angle;

        Spotlight(float constant, float linear, float quad, vec3 direction, float angle, vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
        virtual ~Spotlight();

        virtual void subscribeProgram(GLuint programID);
};

#endif // SPOTLIGHT_H
