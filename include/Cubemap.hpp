#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <GL/glew.h>
#include <GL/glu.h>

#include <string>

#include "CubeGeometry.h"
#include "Shader.h"

class Cubemap {
    public:
        GLuint textureID;

        Cubemap(std::string left, std::string right, std::string top ,std::string bottom, std::string front, std::string back);
        virtual ~Cubemap();

        void Display(mat4 &projection, mat4 &view);

    private:
        std::string textures[6];

        //skybox part
        CubeGeometry skyboxGeometry;
        Shader skyboxShader;
};

#endif // CUBEMAP_H
