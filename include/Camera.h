#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object3D.h"
#include "Input.h"

#define _PI 3.14159265358979323846264338327950288

class Camera : public Object3D {
    public:
        float sensibility;
        float speed;

        Camera(glm::vec3 position, glm::vec3 target, glm::vec3 axis);
        ~Camera();
        void orientate(int xRel, int yRel);
        void translate(Input const &input);
        void lookAt();
        void setTarget(glm::vec3 target);

    private:
        glm::vec3 forwardVector;
        glm::vec3 _axis;
        glm::vec3 sideDisplacement;
};

#endif // CAMERA_H
