#ifndef LIGHT_H
#define LIGHT_H

#include <list>

#include <GL/glew.h>

#include "Object3D.h"

class Light : public Object3D {
    public:
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        Light(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
        virtual void setPosition(glm::vec3 position);
        virtual void addPosition(glm::vec3 position);
        virtual void rotateAroundPoint(glm::vec3 point, glm::vec3 euler);

        void subscribeProgram(GLuint programID);

    protected:
        std::list<GLuint> lightObservers;

        void notifySubscriber(GLuint programID);
        void notifyAllSubscribers();
};

#endif // LIGHT_H
