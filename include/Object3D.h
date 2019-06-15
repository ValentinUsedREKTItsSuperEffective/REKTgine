#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object3D{
    public:
        glm::mat4 matrix; // Local model matrix
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation; // Euler angles

        Object3D();
        virtual ~Object3D();
        virtual void setPosition(glm::vec3 position);
        void addRotationFromEuler(glm::vec3 euler);
        void setRotationFromEuler(glm::vec3 euler);
        void setScale(glm::vec3 scale);
    protected:
        void combineTransformations();
};

#endif // OBJECT3D_H
