#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>

#include <GL/glew.h>

#include "Geometry.h"
#include "Shader.h"

class Framebuffer
{
    public:
        class QuadGeometry : public Geometry {
            public:
                QuadGeometry();
                ~QuadGeometry();
                void load();
        };

        Framebuffer(string vertexShader, string fragmentShader);
        virtual ~Framebuffer();
        void Display();

        GLuint fbo;
        GLuint rbo;
        GLuint textureID;
        QuadGeometry geometry;
        Shader shader;
};

#endif // FRAMEBUFFER_H
