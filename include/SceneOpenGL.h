#ifndef SCENEOPENGL_H
#define SCENEOPENGL_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL2/SDL.h>

#include "Shader.h"
#include "Cube.h"
#include "Crate.h"
#include "Input.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"

#include <iostream>
#include <string>

class SceneOpenGL
{
    public:
        SceneOpenGL(std::string, int, int);
        ~SceneOpenGL();

        bool initWindow();
        bool initGL();
        void ExampleOne();
        void ExampleTwo();

    private:
        SDL_Window* _window;
        SDL_GLContext _context;
        Input _input;
        std::string _title;
        int _width, _height;
};

#endif // SCENEOPENGL_H
