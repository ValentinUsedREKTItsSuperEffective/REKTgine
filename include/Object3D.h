#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glm/glm.hpp>

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
};

#endif // OBJECT3D_H
