#include "glm/ext.hpp"

#include "Scene.h"
#include "Camera.h"
#include "Mesh.hpp"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/Spotlight.h"
#include "Materials/PhongMaterial.h"
#include "Geometry/CubeGeometry.h"
#include "ObjLoader.hpp"
#include "MTLLoader.hpp"

using namespace std;

Scene::Scene(int width, int height) : window(0), context(0), input(), width(width), height(height){}

Scene::~Scene(){
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Scene::initWindow(){
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

    // Création de la fenêtre
    window = SDL_CreateWindow("REKTgine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(window == 0){
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    // Création du contexte OpenGL
    context = SDL_GL_CreateContext(window);

    if(context == 0){
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();

        return false;
    }

    return true;
}

bool Scene::initGL(){
    // Initialisation d'OpenGL
    GLenum err = glewInit();

    if(err != GLEW_OK){
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(err);
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return false;
    }

    return true;
}

// Cubes example
void Scene::ExampleOne(){
    unsigned int frameRate = 1000 / 60;
    Uint32 tic(0), tac(0), timeSpend(0);

     // create camera
    Camera camera(glm::vec3(3,3,3), glm::vec3(0.0,0.0,0.0), 70.0, (double)width/height, 0.1, 100.0);
    input.showCursor(false);
    input.captureCursor(true);

    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f)
    };

    PointLight pointLight(1.f, 0.09f, 0.032f, glm::vec3(1.f), glm::vec3(0.05f), glm::vec3(0.3f), glm::vec3(1.f));
    pointLight.setPosition(glm::vec3(1.2f, 1.0f, 2.0f));

    DirectionalLight dirLight(vec3(-0.2f, -1.0f, -0.3f), vec3(1.f), vec3(0.05f), vec3(0.2f), vec3(1.f));

    Spotlight spotlight(1.f, 0.027f, 0.0028f, vec3(0.f,  0.f, -1.f), radians(12.5f), radians(15.f), vec3(1.f), vec3(0.2f), vec3(0.4f), vec3(1.f));
    spotlight.setPosition(vec3(1.5f, 2.0f, 0.0f));

    CubeGeometry lightGeom(0.1f);
    BaseMaterial lightMat;
    Mesh lightCube(&lightGeom, &lightMat);
    lightCube.setPosition(glm::vec3(1.2f, 1.0f, 2.0f));

    vector<Mesh*> crates;

    // Red Cube
    CubeGeometry redGeom(2.5f);
    MaterialParamaters phongParam;
    phongParam.color = glm::vec3(1.0f, 0.5f, 0.31f);
    phongParam.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    PhongMaterial phongMat(phongParam);
    Mesh* phongCube = new Mesh(&redGeom, &phongMat);
    phongCube->setPosition(glm::vec3(-7.3f,  0.0f, -7.5f));
    phongCube->useLight(pointLight);
    phongCube->useLight(dirLight);
    phongCube->useLight(spotlight);
    crates.push_back(phongCube);

    // Emerald Cube
    CubeGeometry emeraldGeom(1.f);
    MaterialParamaters phongParamEmerald;
    phongParamEmerald.color = glm::vec3(0.07568f, 0.61424f, 0.07568f);
    phongParamEmerald.ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
    phongParamEmerald.specular = glm::vec3(0.633f, 0.727811f, 0.633f);
    phongParamEmerald.emissiveMapSrc = "Ressources/Materials/matrix.jpg";
    PhongMaterial phongMatE(phongParamEmerald);
    Mesh* emeraldCube = new Mesh(&emeraldGeom, &phongMatE);
    emeraldCube->setPosition(glm::vec3(1.5f,  0.2f, -1.5f));
    emeraldCube->useLight(pointLight);
    emeraldCube->useLight(dirLight);
    emeraldCube->useLight(spotlight);
    crates.push_back(emeraldCube);

    // Textured Cube
    MaterialParamaters phongParamTex;
    phongParamTex.textureSrc = "Ressources/Materials/container2.png";
    phongParamTex.specular = glm::vec3(0.633f, 0.727811f, 0.633f);
    phongParamTex.specularMapSrc = "Ressources/Materials/container2_specular.png";
    PhongMaterial phongMatTex(phongParamTex);
    Mesh* texCube = new Mesh(&emeraldGeom, &phongMatTex);
    texCube->setPosition(glm::vec3(1.5f,  2.0f, -2.5f));
    texCube->useLight(pointLight);
    texCube->useLight(dirLight);
    texCube->useLight(spotlight);
    crates.push_back(texCube);

    Mesh* texCubeBis = new Mesh(&emeraldGeom, &phongMatTex);
    texCubeBis->setPosition(glm::vec3(2.6f,  2.0f, -2.5f));
    texCubeBis->useLight(pointLight);
    texCubeBis->useLight(dirLight);
    texCubeBis->useLight(spotlight);
    crates.push_back(texCubeBis);

    for(int i = 0; i < 7; i++){
        Mesh* crate = new Mesh(&emeraldGeom, &phongMatTex);
        crate->setPosition(cubePositions[i]);
        crate->setRotationFromEuler(vec3(radians(rand() * 356.f), radians(rand() * 356.f), radians(rand() * 356.f)));
        crate->useLight(pointLight);
        crate->useLight(dirLight);
        crate->useLight(spotlight);
        crates.push_back(crate);
    }

    ObjLoader loader;
    Geometry suzanneGeometry;
    loader.Load("Ressources/Models/backpack.obj", suzanneGeometry);

    MTLLoader MTLLoader;
    MaterialParamaters backpackMatParam;
    MTLLoader.Load("Ressources/Materials/backpack/", "backpack.mtl", backpackMatParam);
    backpackMatParam.inverseImage = false;
    PhongMaterial backpackMat(backpackMatParam);

    Mesh backpack(&suzanneGeometry, &backpackMat);
    backpack.setPosition(4.f, 0.f, 0.f);
    backpack.useLight(pointLight);
    backpack.useLight(dirLight);
    backpack.useLight(spotlight);

    glm::mat4 view;

    glEnable(GL_DEPTH_TEST);

     while(!input.isEnd){

        tic = SDL_GetTicks();

        input.updateEvent();

        if(input.getKey(SDL_SCANCODE_ESCAPE))
            break;

        camera.translate(input);

        // Clean buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera location
        view = camera.getViewMatrix();

        phongCube->addRotationFromEuler(glm::vec3(0.01, 0., 0.));

        phongMat.setViewPosition(camera.position);
        phongMatE.setViewPosition(camera.position);
        phongMatTex.setViewPosition(camera.position);
        backpackMat.setViewPosition(camera.position);

        pointLight.rotateAroundPoint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.05, 0.0));
        lightCube.rotateAroundPoint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.05, 0.0));
        lightCube.display(camera.projectionMatrix, view);

        for(int i = 0; i < 11; i++){
            crates[i]->display(camera.projectionMatrix, view);
        }

        backpack.display(camera.projectionMatrix, view);

        SDL_GL_SwapWindow(window);

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
