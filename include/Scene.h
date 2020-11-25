#ifndef SCENEOPENGL_H
#define SCENEOPENGL_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL2/SDL.h>

#include "Input.h"

using namespace glm;

class Scene{
    public:
        Scene();
        ~Scene();

        bool initWindow();
        bool initGL();
        void ExampleOne();

    private:
        SDL_Window* window;
        SDL_GLContext context;
        Input input;
};

#endif // SCENEOPENGL_H
