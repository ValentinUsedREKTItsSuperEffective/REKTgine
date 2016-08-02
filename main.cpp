#include "SceneOpenGL.h"

int main(int argc, char **argv)
{
    // Notre scène

    SceneOpenGL scene("caca", 800, 600);

    if(scene.initWindow() == false)
        return -1;

    if(scene.initGL() == false)
        return -1;

    //Boucle principale
    scene.mainLoop();

    return 0;
}
