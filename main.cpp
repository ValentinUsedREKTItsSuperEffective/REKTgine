#include <iostream>

#include "SceneOpenGL.h"

#include "Vector3.h"
#include "Ray.h"
#include "HitableList.h"
#include "rt_Sphere.h"

Vector3 color(Ray& ray, Hitable* world){
    HitRecord record;
    if(world->hit(ray, 0.0, 100000000.0, record)){
        return 0.5*Vector3(record.normal.x() + 1, record.normal.y() + 1, record.normal.z() + 1);
    } else {
        ray.direction.normalize();
        double t = 0.5*(ray.direction.y() + 1.0);
        return (1.0 - t)*Vector3(1.0, 1.0, 1.0)+ t*Vector3(0.5, 0.7, 1.0);
    }
}

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
        // This is the implementation of the 3 documents : Raytracing in a Week-end, the next week-end, and the rest of your life by Peter Shirley
        int x = 400;
        int y = 200;

        Vector3 lowerLeftCorner(-2.0, -1.0, -1.0);
        Vector3 cameraLens(4.0, 2.0, 0.0);
        Vector3 origin(0.0, 0.0, 0.0);

        Hitable *list[2];
        list[0] = new rt_Sphere(Vector3(0, 0, -1), 0.5);
        list[1] = new rt_Sphere(Vector3(0, -100.5, -1), 100);
        HitableList *world = new HitableList(list, 2);

        FILE *fp = fopen("output.ppm", "wb");

        (void) fprintf(fp,"P3\n%d %d\n255\n", x, y);

        for(int j = y -1; j >= 0; j--){
            for(int i = 0; i < x; i++){
                Vector3 uv(double(i) / double(x), double(j) / double(y), 0.0);
                Ray ray(origin, lowerLeftCorner + uv*cameraLens);
                Vector3 col = color(ray, world)* double(255.99);

                (void) fprintf(fp,"%f %f %f\n", col.r(), col.g(), col.b());
            }
        }

        (void) fclose(fp);
    }

    return 0;
}
