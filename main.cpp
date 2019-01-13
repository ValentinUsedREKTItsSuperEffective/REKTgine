#include <iostream>

#include "SceneOpenGL.h"

#include "Vector3.h"
#include "Ray.h"

Vector3 color(Ray& ray){
    ray.direction.normalize();
    double t = 0.5*(ray.direction.y() + 1);
    return (1.0 - t)*Vector3(1.0, 1.0, 1.0)+ t*Vector3(0.5, 0.7, 1.0);
}

int main(int argc, char **argv){

    bool realtime = false;

    if (realtime) {
        // Notre sc�ne
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

        Vector3 lowerLeftCorner(-2.0, -1.0, -1.0);
        Vector3 cameraLens(4.0, 2.0, 0.0);
        Vector3 origin(0.0, 0.0, 0.0);

        FILE *fp = fopen("output.ppm", "wb");

        (void) fprintf(fp,"P3\n%d %d\n255\n", x, y);

        for(int j = y -1; j >= 0; j--){
            for(int i = 0; i < x; i++){
                Vector3 uv(double(i) / double(x), double(j) / double(y), 0.0);
                Ray ray(origin, lowerLeftCorner + uv*cameraLens);
                Vector3 col = color(ray)* double(255.99);

                (void) fprintf(fp,"%f %f %f\n", col.r(), col.g(), col.b());
            }
        }

        (void) fclose(fp);
    }

    return 0;
}
