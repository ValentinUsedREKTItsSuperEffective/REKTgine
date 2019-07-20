#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object3D.h"
#include "Shader.h"
#include "Materials/BaseMaterial.h"

class Cube : public Object3D{
    public:
        Cube(float dim, BaseMaterial *material);
        ~Cube();
        virtual void load();
        virtual void display(mat4 &projection, mat4 &modelView);

        inline void useLight(Light &light){
            material->useLight(light);
        }

    protected:
        BaseMaterial *material;
        float positions[108];
        float uvs[72];
        float normals[108];

        GLuint vbo;
        GLuint vao;
        // TODO : Add ebo
};

#endif // CUBE_H
