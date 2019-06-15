#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Object3D{
    public:
        // ATTRIBUTES
        glm::mat4 matrix; // Local model matrix
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation; // Euler angles

        // Functions
        Object3D();
        virtual ~Object3D();
        virtual void setPosition(glm::vec3 position);
        void setRotation(glm::vec3 rotation);
        void setScale(glm::vec3 scale);
    protected:
        void combineTransformations();
};

#endif // OBJECT3D_H
