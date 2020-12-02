#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

#include "Texture.h"
#include "Geometry.h"

class Framebuffer
{
    public:
        class QuadGeometry : public Geometry {
            public:
                QuadGeometry();
                ~QuadGeometry();
        };

        Framebuffer();
        virtual ~Framebuffer();

        GLuint fbo;
        GLuint rbo;
        Texture texture;
};

#endif // FRAMEBUFFER_H
