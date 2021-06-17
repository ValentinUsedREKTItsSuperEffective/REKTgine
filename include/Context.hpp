#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>

class Context
{
    public:
        Context();
        virtual ~Context();

        bool InitWindow();
        bool InitGL();
        void SwapWindow();

    private:
        SDL_Window* window;
        SDL_GLContext glContext;

        void DestroyContext();
};

#endif // CONTEXT_H
