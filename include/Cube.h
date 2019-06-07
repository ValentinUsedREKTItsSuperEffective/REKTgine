#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object3D.h"
#include "Shader.h"


// Class Cube

class Cube : public Object3D{
    public:
        Cube(float dim, std::string vertexShader, std::string fragmentShader);
        ~Cube();
        virtual void display(glm::mat4 &projection, glm::mat4 &modelView);
        virtual void load();

    protected:
        Shader shader;
        float positions[108];
        float uvs[72];

        GLuint vbo;
        GLuint vao;
};

#endif // CUBE_H
