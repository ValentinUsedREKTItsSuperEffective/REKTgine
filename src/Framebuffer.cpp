#include "Framebuffer.hpp"

Framebuffer::Framebuffer(){
    glGenFramebuffers(1, &fbo);
}

Framebuffer::~Framebuffer(){
    glDeleteFramebuffers(1, &fbo);
}
