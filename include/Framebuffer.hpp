#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

#include "Texture.h"

class Framebuffer
{
    public:
        Framebuffer();
        virtual ~Framebuffer();

        GLuint fbo;
        GLuint rbo;
        Texture texture;
};

#endif // FRAMEBUFFER_H
