#include <iostream>

#include "SceneOpenGL.h"

#include "Vector3.h"
#include "Ray.h"
#include "HitableList.h"
#include "rt_Sphere.h"
#include "rt_Camera.h"
#include "Material_RT.h"

Vector3 getPointInUnitSphere(){
    Vector3 p;
    do{
        p = 2.0 * Vector3(frand(),frand(),frand()) - Vector3(1.0);
    } while(p.lengthSq() >= 1.0);
    return p;
}

Vector3 color(Ray& ray, Hitable* world, int depth){
    HitRecord record;
    if(world->hit(ray, 0.001, 100000000.0, record)){
        Ray scattered;
        Vector3 attenuation;
        if(depth < 50 && record.material->scatter(ray, record, attenuation, scattered)){
            return attenuation*color(scattered, world, depth+1);
        } else {
            return Vector3(0.0, 0.0, 0.0);
        }
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

        Hitable *list[4];
        list[0] = new rt_Sphere(Vector3(0, 0, -1), 0.5, new Lambertian_RT(Vector3(0.8, 0.3, 0.3)));
        list[1] = new rt_Sphere(Vector3(0, -100.5, -1), 100, new Lambertian_RT(Vector3(0.8, 0.8, 0.0)));
        list[2] = new rt_Sphere(Vector3(1, 0, -1), 0.5, new Metal_RT(Vector3(0.8, 0.6, 0.2), 0.0));
        list[3] = new rt_Sphere(Vector3(-1, 0, -1), 0.5, new Dielectric_RT(1.5));
        HitableList *world = new HitableList(list, 4);

        Vector3 lookFrom(3,3,2);
        Vector3 lookAt(0,0,-1);
        float distToFocus = (lookFrom - lookAt).length();
        float aperture = 2.0;
        rt_Camera camera(lookFrom, lookAt, Vector3(0,1,0), 20, x/y, aperture, distToFocus);

        FILE *fp = fopen("output.ppm", "wb");

        (void) fprintf(fp,"P3\n%d %d\n255\n", x, y);

        for(int j = y -1; j >= 0; j--){
            for(int i = 0; i < x; i++){
                Vector3 col(0, 0, 0);
                for(int s = 0; s < nSample; s++){
                    Ray ray = camera.getRay(double(i + frand()) / double(x), double(j + frand()) / double(y));
                    col += color(ray, world, 0);
                }
                col /= double(nSample);
                col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

                (void) fprintf(fp,"%f %f %f\n", col.r()* double(255.99), col.g()* double(255.99), col.b()* double(255.99));
            }
        }

        (void) fclose(fp);
    }

    return 0;
}
