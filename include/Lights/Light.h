#ifndef LIGHT_H
#define LIGHT_H

#include <list>

#include <GL/glew.h>

#include "Object3D.h"

using namespace glm;

// TODO : Make it abstract
class Light : public Object3D {
    public:
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        Light(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
        virtual void setPosition(vec3 position);
        virtual void addPosition(vec3 position);
        virtual void rotateAroundPoint(vec3 point, vec3 euler);

        virtual void subscribeProgram(GLuint programID);

    protected:
        std::list<GLuint> lightObservers;

        void notifySubscriber(GLuint programID);
        void notifyAllSubscribers();
};

#endif // LIGHT_H
