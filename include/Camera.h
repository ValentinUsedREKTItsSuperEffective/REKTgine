#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"

#define _PI 3.14159265358979323846264338327950288

class Camera
{
    public:
        glm::vec3 _eye;

        Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 axis);
        ~Camera();
        void orientate(int xRel, int yRel);
        void translate(Input const &input);
        void lookAt(glm::mat4 &modelView);
        void setTarget(glm::vec3 target);
        void setPosition(glm::vec3 position);
        void setSensibility(float sensibility);
        void setSpeed(float speed);

    private:
        float _theta;
        float _phi;
        glm::vec3 _orientation;
        glm::vec3 _axis;
        glm::vec3 _sideDisplacement;
        glm::vec3 _target;

        float _sensibility;
        float _speed;
};

#endif // CAMERA_H
