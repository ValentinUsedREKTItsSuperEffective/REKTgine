#include <iostream>

#include "SceneOpenGL.h"

#include "Vector3.h"
#include "Ray.h"
#include "HitableList.h"
#include "rt_Sphere.h"
#include "rt_Camera.h"

double frand(){
    return double(rand()) / double(RAND_MAX);
}

Vector3 getPointInUnitSphere(){
    Vector3 p;
    do{
        p = 2.0 * Vector3(frand(),frand(),frand()) - Vector3(1.0);
    } while(p.lengthSq() >= 1.0);
    return p;
}

Vector3 color(Ray& ray, Hitable* world, int i){
    HitRecord record;
    if(world->hit(ray, 0.001, 100000000.0, record)){
        Vector3 p = record.p + record.normal + getPointInUnitSphere();
        Ray r(record.p, p - record.p);
        return 0.5*color(r, world, i+1);
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

        int nSample = 100;

        Hitable *list[2];
        list[0] = new rt_Sphere(Vector3(0, 0, -1), 0.5);
        list[1] = new rt_Sphere(Vector3(0, -100.5, -1), 100);
        HitableList *world = new HitableList(list, 2);

        rt_Camera camera;

        FILE *fp = fopen("output.ppm", "wb");

        (void) fprintf(fp,"P3\n%d %d\n255\n", x, y);

        for(int j = y -1; j >= 0; j--){
            for(int i = 0; i < x; i++){
                Vector3 col(0, 0, 0);
                for(int s = 0; s < nSample; s++){
                    Vector3 uv(double(i + frand()) / double(x), double(j + frand()) / double(y), 0.0);
                    Ray ray = camera.getRay(uv);
                    col += color(ray, world, 0)* double(255.99);
                }
                col /= double(nSample);

                (void) fprintf(fp,"%f %f %f\n", col.r(), col.g(), col.b());
            }
        }

        (void) fclose(fp);
    }

    return 0;
}
