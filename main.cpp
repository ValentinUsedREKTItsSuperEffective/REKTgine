#include <iostream>

#include "SceneOpenGL.h"

int main(int argc, char **argv){

    bool realtime = false;

    if (realtime) {
        // Notre scène
        SceneOpenGL scene("caca", 800, 600);

        if(scene.initWindow() == false)
            return -1;

        if(scene.initGL() == false)
            return -1;

        //Boucle principale
        scene.ExampleOne();
    } else {
        // raytracing
        int x = 400;
        int y = 200;

        FILE *fp = fopen("output.ppm", "wb");

        (void) fprintf(fp,"P3\n%d %d\n255\n", x, y);

        for(int j = y -1; j >= 0; j--){
            for(int i = 0; i < x; i++){
                double r,g,b;
                r = (double(i) / double(x)) * double(255.99);
                g = (double(j) / double(y)) * double(255.99);
                b = 0.2 * 255.99;

                (void) fprintf(fp,"%f %f %f\n", r, g, b);
            }
        }

        (void) fclose(fp);
    }

    return 0;
}
