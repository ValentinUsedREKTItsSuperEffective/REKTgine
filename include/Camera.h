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
        void lookAt(glm::mat4 &modelView);
        void setTarget(glm::vec3 target);
        virtual void setPosition(glm::vec3 position);

    private:
        float _theta;
        float _phi;
        glm::vec3 _orientation;
        glm::vec3 _axis;
        glm::vec3 sideDisplacement;
        glm::vec3 target;
};

#endif // CAMERA_H
