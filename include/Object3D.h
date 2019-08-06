#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Object3D{
    public:
        std::string name;
        mat4 model; // Local model matrix
        vec3 position;
        vec3 scale;
        vec3 rotation; // Euler angles

        Object3D();
        virtual ~Object3D();
        virtual void setPosition(vec3 position);
        virtual void setPosition(float x, float y, float z);
        virtual void addPosition(vec3 position);
        void addRotationFromEuler(vec3 euler);
        void setRotationFromEuler(vec3 euler);
        virtual void rotateAroundPoint(vec3 point, vec3 euler);
        void setScale(vec3 scale);
        void setScale(float scale);
        void addScale(vec3 scale);
    protected:
        mat4 eulerToMat4(vec3 euler);
        void combineTransformations();
};

#endif // OBJECT3D_H
