#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

class Framebuffer
{
    public:
        Framebuffer();
        virtual ~Framebuffer();

    protected:
        GLuint fbo;
};

#endif // FRAMEBUFFER_H
