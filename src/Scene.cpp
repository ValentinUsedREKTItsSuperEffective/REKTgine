#include "glm/ext.hpp"

#include "Scene.h"
#include "Screen.hpp"
#include "Camera.h"
#include "Mesh.hpp"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/Spotlight.h"
#include "Materials/PhongMaterial.h"
#include "Geometry/CubeGeometry.h"
#include "ObjLoader.hpp"
#include "MTLLoader.hpp"
#include "Sprite.hpp"
#include "Billboard.hpp"
#include "Framebuffer.hpp"
#include "Cubemap.hpp"

using namespace std;

Scene::Scene(Context* context) : context(context), input(){}

Scene::~Scene(){}

void Scene::Add(Mesh* mesh){
    // Incomplete function, I don't know what a Scene::Add function have to do yet
    for(auto it = lights.begin(); it != lights.end(); ++it){
        mesh->useLight(*(*it));
    }
}

// Cubes example
void Scene::ExampleOne(){
    // TODO : Random class
    srand (time(NULL));

    unsigned int frameRate = 1000 / 60;
    Uint32 tic(0), tac(0), timeSpend(0);

     // create camera
    Camera camera(glm::vec3(3,3,3), glm::vec3(0.0,0.0,0.0), 70.0, (double)Screen::width/Screen::height, 0.1, 100.0);
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
    lights.push_back(&pointLight);

    DirectionalLight dirLight(vec3(-0.2f, -1.0f, -0.3f), vec3(1.f), vec3(0.05f), vec3(0.2f), vec3(1.f));
    lights.push_back(&dirLight);

    Spotlight spotlight(1.f, 0.027f, 0.0028f, vec3(0.f,  0.f, -1.f), radians(12.5f), radians(15.f), vec3(1.f), vec3(0.05f), vec3(0.4f), vec3(1.f));
    spotlight.setPosition(vec3(1.5f, 2.0f, 0.0f));
    lights.push_back(&spotlight);

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
    Add(phongCube);
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
    Add(emeraldCube);
    crates.push_back(emeraldCube);

    // Textured Cube
    MaterialParamaters phongParamTex;
    phongParamTex.textureSrc = "Ressources/Materials/container2.png";
    phongParamTex.specular = glm::vec3(0.633f, 0.727811f, 0.633f);
    phongParamTex.specularMapSrc = "Ressources/Materials/container2_specular.png";
    PhongMaterial phongMatTex(phongParamTex);
    Mesh* texCube = new Mesh(&emeraldGeom, &phongMatTex);
    texCube->setPosition(glm::vec3(1.5f,  2.0f, -2.5f));
    Add(texCube);
    crates.push_back(texCube);

    Mesh* texCubeBis = new Mesh(&emeraldGeom, &phongMatTex);
    texCubeBis->setPosition(glm::vec3(2.6f,  2.0f, -2.5f));
    Add(texCubeBis);
    crates.push_back(texCubeBis);

    for(int i = 0; i < 7; i++){
        Mesh* crate = new Mesh(&emeraldGeom, &phongMatTex);
        crate->setPosition(cubePositions[i]);
        crate->setRotationFromEuler(vec3(radians((float)(rand() % 365)), radians((float)(rand() % 365)), radians((float)(rand() % 365))));
        Add(crate);
        crates.push_back(crate);
    }

    /*
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
    // BUG : caisse non affiche sans cette ligne MAIS cube lumineux trop gros
    backpack.setRotationFromEuler(vec3());
    backpack.useLight(pointLight);
    backpack.useLight(dirLight);
    backpack.useLight(spotlight);
    */

    // Outline
    MaterialParamaters outlineMatParam;
    outlineMatParam.color = vec3(245.f, 0.f, 0.f);
    BaseMaterial outlineMat(outlineMatParam);

    // Blending
    // TODO : Detecter les textures transparentes pour les Sprites
    Sprite transparent_window("Ressources/Materials/blending_transparent_window.png");
    transparent_window.setPosition(-4.f, 0.f, 0.f);

    Billboard transparent_window2("Ressources/Materials/blending_transparent_window.png", &camera);
    transparent_window2.setPosition(-3.5f, 0.f, -.2f);

    Sprite transparent_window3("Ressources/Materials/blending_transparent_window.png");
    transparent_window3.setPosition(-4.5f, 0.f, -.4f);

    // TODO : les objets transparent active GL_BLEND une seule fois
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 view;

    glEnable(GL_DEPTH_TEST);

    //Outline
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);

    //Culling
    glEnable(GL_CULL_FACE);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

     while(!input.isEnd){

        tic = SDL_GetTicks();

        input.updateEvent();

        if(input.getKey(SDL_SCANCODE_ESCAPE))
            break;

        camera.translate(input);

        // Clean buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glStencilMask(0x00);

        // Camera location
        view = camera.getViewMatrix();

        phongCube->addRotationFromEuler(glm::vec3(0.01, 0., 0.));

        phongMat.setViewPosition(camera.position);
        phongMatE.setViewPosition(camera.position);
        phongMatTex.setViewPosition(camera.position);
        //backpackMat.setViewPosition(camera.position);

        pointLight.rotateAroundPoint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.05, 0.0));
        lightCube.rotateAroundPoint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.05, 0.0));
        lightCube.display(camera.projectionMatrix, view);

        for(int i = 0; i < 10; i++){
            crates[i]->display(camera.projectionMatrix, view);
        }

        // Outline
        // This work only for non-holed centered object, otherwise the outline will be shift or simply won't fit
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        crates[10]->setScale(1.f);
        crates[10]->SetMaterial(&phongMatTex);
        crates[10]->display(camera.projectionMatrix, view);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        crates[10]->setScale(1.1f);
        crates[10]->SetMaterial(&outlineMat);
        crates[10]->display(camera.projectionMatrix, view);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);

        //backpack.display(camera.projectionMatrix, view);

        // Objets transparents apres objets opaques
        // TODO : Faut que les objets transparents soient rendu selon leur distance avec la camera, le plus loin en premier
        transparent_window3.display(camera.projectionMatrix, view);
        transparent_window2.display(camera.projectionMatrix, view);
        transparent_window.display(camera.projectionMatrix, view);

        context->SwapWindow();

        tac = SDL_GetTicks();
        timeSpend = tac - tic;
        if(timeSpend < frameRate){
            SDL_Delay(frameRate-timeSpend);
        }
     }

    for(int i = 0; i < 11; i++){
        delete crates[i];
    }
}

void Scene::ExampleFramework(){
    // TODO : Random class
    srand (time(NULL));

    unsigned int frameRate = 1000 / 60;
    Uint32 tic(0), tac(0), timeSpend(0);

     // create camera
    Camera camera(glm::vec3(3,3,3), glm::vec3(0.0,0.0,0.0), 70.0, (double)Screen::width/Screen::height, 0.1, 100.0);
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
        crate->setRotationFromEuler(vec3(radians((float)(rand() % 365)), radians((float)(rand() % 365)), radians((float)(rand() % 365))));
        crate->useLight(pointLight);
        crate->useLight(dirLight);
        crate->useLight(spotlight);
        crates.push_back(crate);
    }

    Sprite transparent_window("Ressources/Materials/blending_transparent_window.png");
    transparent_window.setPosition(-4.f, 0.f, 0.f);

    glm::mat4 view;

    glEnable(GL_DEPTH_TEST);

    // Framebuffer
    Framebuffer framebuffer("Shaders/PostEffects/framebuffer.vert", "Shaders/PostEffects/blur.frag");

    //Culling
    glEnable(GL_CULL_FACE);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

     while(!input.isEnd){

        tic = SDL_GetTicks();

        input.updateEvent();

        if(input.getKey(SDL_SCANCODE_ESCAPE))
            break;

        camera.translate(input);

        // bind the framebuffer before clearing buffer otherwise the wrong framebuffer's color will be clear
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.fbo);

        // Clean buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera location
        view = camera.getViewMatrix();

        phongCube->addRotationFromEuler(glm::vec3(0.01, 0., 0.));

        phongMat.setViewPosition(camera.position);
        phongMatE.setViewPosition(camera.position);
        phongMatTex.setViewPosition(camera.position);

        pointLight.rotateAroundPoint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.05, 0.0));
        lightCube.rotateAroundPoint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.05, 0.0));
        lightCube.display(camera.projectionMatrix, view);

        for(int i = 0; i < 11; i++){
            crates[i]->display(camera.projectionMatrix, view);
        }

        // Objets transparents apres objets opaques
        // TODO : Faut que les objets transparents soient rendu selon leur distance avec la camera, le plus loin en premier
        transparent_window.display(camera.projectionMatrix, view);

        framebuffer.Display();

        context->SwapWindow();

        tac = SDL_GetTicks();
        timeSpend = tac - tic;
        if(timeSpend < frameRate){
            SDL_Delay(frameRate-timeSpend);
        }
     }

    for(int i = 0; i < 11; i++){
        delete crates[i];
    }
}

void Scene::ExampleSkybox(){
    // TODO : Random class
    srand (time(NULL));

    unsigned int frameRate = 1000 / 60;
    Uint32 tic(0), tac(0), timeSpend(0);

     // create camera
    Camera camera(glm::vec3(3,3,3), glm::vec3(0.0,0.0,0.0), 70.0, (double)Screen::width/Screen::height, 0.1, 100.0);
    input.showCursor(false);
    input.captureCursor(true);

    Shader reflectionShader("Shaders/environment.vert", "Shaders/environment.frag");

    // Reflexion cube
    CubeGeometry reflexionCube(2.5f);

    string matPath = "Ressources/Materials/";
    string skyboxPath = matPath + "skybox/";

    Cubemap skybox(
        skyboxPath + "left.jpg",
        skyboxPath + "right.jpg",
        skyboxPath + "top.jpg",
        skyboxPath + "bottom.jpg",
        skyboxPath + "front.jpg",
        skyboxPath + "back.jpg"
    );

    glUseProgram(reflectionShader.programID);
    reflectionShader.bindInt("skybox", GL_TEXTURE0);

    glm::mat4 model = glm::mat4(1.0f);
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

        glUseProgram(reflectionShader.programID);
        reflectionShader.bindMat4("model", model);
        reflectionShader.bindMat4("view", view);
        reflectionShader.bindMat4("projection", camera.projectionMatrix);
        reflectionShader.bindFloat3("cameraPosition", camera.position);

        reflexionCube.bindVertexArray();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.textureID);
        glDrawElements(GL_TRIANGLES, reflexionCube.indexes.size(), GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
        glUseProgram(0);

        skybox.Display(camera.projectionMatrix, view);

        context->SwapWindow();

        tac = SDL_GetTicks();
        timeSpend = tac - tic;
        if(timeSpend < frameRate){
            SDL_Delay(frameRate-timeSpend);
        }
     }
}
