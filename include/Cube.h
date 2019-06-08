#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object3D.h"
#include "Shader.h"
#include "BaseMaterial.h"


// Class Cube

class Cube : public Object3D{
    public:
        Cube(float dim, BaseMaterial *material);
        ~Cube();
        virtual void load();
        virtual void display(glm::mat4 &projection, glm::mat4 &modelView);

    protected:
        BaseMaterial *material;
        float positions[108];
        float uvs[72];

        GLuint vbo;
        GLuint vao;
};

#endif // CUBE_H
