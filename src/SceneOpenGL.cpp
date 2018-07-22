#include "SceneOpenGL.h"
#include "Light.h"

#include "glm/ext.hpp"

using namespace std;

SceneOpenGL::SceneOpenGL(std::string title, int width, int height) : _window(0), _context(0), _input(), _title(title), _width(width), _height(height)
{

}

SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool SceneOpenGL::initWindow(){

    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
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

    // Création de la fenêtre
    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(_window == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    // Création du contexte OpenGL
    _context = SDL_GL_CreateContext(_window);

    if(_context == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(_window);
        SDL_Quit();

        return false;
    }

    return true;
}

bool SceneOpenGL::initGL(){

    // Initialisation d'OpenGL
    GLenum err = glewInit();

    if(err != GLEW_OK){
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(err);
        SDL_GL_DeleteContext(_context);
        SDL_DestroyWindow(_window);
        SDL_Quit();

        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

// Cubes example
void SceneOpenGL::ExampleOne(){
    unsigned int frameRate = 1000 / 60;
    Uint32 tic(0), tac(0), timeSpend(0);

    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Cube cube(0.5f,"Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
    // cube.load();

    vector<Crate*> crates;
    for(int i = 0; i<10; i++){
        Crate* crate = new Crate(1.f,"Shaders/texture.vert", "Shaders/texture.frag","Ressources/photorealistic/photorealistic_crate/crate12.jpg");
        crate->load();
        crate->SetPosition(cubePositions[i]);
        crates.push_back(crate);
    }

    // matrix
    glm::mat4 projection;
    projection = glm::perspective(70.0,(double)_width/_height,1.0,100.0);

     // create camera
    Camera camera(glm::vec3(3,3,3),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    _input.showCursor(false);
    _input.captureCursor(true);

     glm::mat4 view, model;

     while(!_input.isEnd()){

        tic = SDL_GetTicks();

        _input.updateEvent();

        if(_input.getKey(SDL_SCANCODE_ESCAPE))
            break;

        camera.translate(_input);

        // Clean buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera location
        camera.lookAt(view);

        for(int i = 0; i<10; i++){
            crates[i]->display(projection,view);
        }

        SDL_GL_SwapWindow(_window);

        tac = SDL_GetTicks();
        timeSpend = tac - tic;
        if(timeSpend < frameRate){
            SDL_Delay(frameRate-timeSpend);
        }
     }

    for(int i = 0; i<10; i++){
        delete crates[i];
    }
}

void SceneOpenGL::ExampleTwo(){
    unsigned int frameRate = 1000 / 60;
    Uint32 tic(0), tac(0), timeSpend(0);

    // Load mesh
    Light light(glm::vec3(1.f), "Shaders/light.vert", "Shaders/light.frag");
    light.setPosition(glm::vec3( 0.0f,  0.0f,  0.0f));
    light.load();

    Mesh suzanne("Ressources/suzanne.obj","Shaders/blinnPhong.vert", "Shaders/blinnPhong.frag","Ressources/uvmap.tga");
    suzanne.load();
    suzanne.useLight(light);

    // load texture

    // create shader

    // matrix
    glm::mat4 projection, modelView;
    // TODO : envoyer les matrices de projection et de vue une seule fois et pas à chaque appel de la fonction display

    projection = glm::perspective(70.0,(double)_width/_height,1.0,100.0);

    // create camera
    Camera camera(glm::vec3(3,3,3),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    _input.showCursor(false);
    _input.captureCursor(true);

    while(!_input.isEnd()){

        tic = SDL_GetTicks();

        _input.updateEvent();

        if(_input.getKey(SDL_SCANCODE_ESCAPE))
            break;

        camera.translate(_input);

        // Clean buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera location
        glm::mat4 view;
        camera.lookAt(view);

        glm::mat4 model;
        model = glm::translate(model,light.getPosition());
        modelView = view * model;
        light.display(projection, modelView);

        model = glm::translate(model,glm::vec3( 2.4f, -0.4f, -3.5f));
        modelView = view * model;
        suzanne.display(projection, modelView);

/*
        // Shader activation
        glUseProgram(shader.getProgramID());

            // Rendering
            // glVertexAttribPointer + glEnableVertexAttribArray
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,vertex);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,coordTex);
            glEnableVertexAttribArray(2);

            // uniform
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(),"modelView"),1,GL_FALSE,glm::value_ptr(modelView));

            // glBindTexture
            glBindTexture(GL_TEXTURE_2D, tex.getID());

            // glDrawArrays
            glDrawArrays(GL_TRIANGLES,0,6);

            // unbind texture
            glBindTexture(GL_TEXTURE_2D,0);

            // glDisableVertexAttribArray
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(2);

        // Shader disactivation
        glUseProgram(0);
*/
        SDL_GL_SwapWindow(_window);

        tac = SDL_GetTicks();
        timeSpend = tac - tic;
        if(timeSpend < frameRate)
            SDL_Delay(frameRate-timeSpend);
    }

}
