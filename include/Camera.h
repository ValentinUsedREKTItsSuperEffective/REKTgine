#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object3D.h"
#include "Input.h"

#define _PI 3.14159265358979323846264338327950288

using namespace glm;

class Camera : public Object3D {
    public:
        mat4 projectionMatrix;

        float sensibility;
        float speed;

        Camera(vec3 position, vec3 target, double fov, double aspect, double near, double far);
        ~Camera();
        void orientate(int xRel, int yRel);
        void translate(Input const &input);
        mat4 getViewMatrix();

    private:
        vec3 direction;
        vec3 right;
        vec3 up;
        vec3 worldUp;
};

#endif // CAMERA_H
