#include "Context.hpp"
#include "Screen.hpp"

Context::Context() : window(0), glContext(0){}

Context::~Context(){
   DestroyContext();
}

bool Context::InitWindow(){
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("REKTgine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen::width, Screen::height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(window == 0){
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    // Création du contexte OpenGL
    glContext = SDL_GL_CreateContext(window);

    if(glContext == 0){
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();

        return false;
    }

    return true;
}

bool Context::InitGL(){
    // Initialisation d'OpenGL
    GLenum err = glewInit();

    if(err != GLEW_OK){
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(err);
        DestroyContext();
        return false;
    }

    return true;
}

void Context::SwapWindow(){
    SDL_GL_SwapWindow(window);
}

void Context::DestroyContext(){
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
