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

        Camera(glm::vec3 position, glm::vec3 target);
        ~Camera();
        void orientate(int xRel, int yRel);
        void translate(Input const &input);
        glm::mat4 getViewMatrix();

    private:
        glm::vec3 direction;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 worldUp;
};

#endif // CAMERA_H
