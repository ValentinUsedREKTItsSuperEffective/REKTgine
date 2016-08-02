#ifndef CUBE_H
#define CUBE_H


#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


// Class Cube

class Cube
{
    public:
        Cube(float dim, std::string vertexShader, std::string fragmentShader);
        ~Cube();
        void display(glm::mat4 &projection, glm::mat4 &modelView);
        void load();

    protected:
        Shader _shader;
        float _vertex[108];
        float _color[108];

        GLuint _vbo;
        int _sizeVerticesBytes;
        int _sizeColorBytes;
};

#endif // CUBE_H
