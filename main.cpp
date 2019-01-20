#include <iostream>

#include "SceneOpenGL.h"

#include "Vector3.h"
#include "Ray.h"

double hitSphere(const Vector3& center, float radius, const Ray& r){
    Vector3 oc = r.origin - center;
    float a = dot(r.direction, r.direction);
    float b = 2.0 * dot(oc, r.direction);
    float c = dot(oc, oc) - radius*radius;
    float det = b*b - 4*a*c;
    if(det < 0){
        return -1.0;
    } else {
        return (-b - sqrt(det)) / 2.0*a;
    }
}

Vector3 color(Ray& ray){
    double t = hitSphere(Vector3(0, 0, -1), 0.5, ray);
    if(t > 0.0){
        Vector3 N = normalize(ray.projectAt(t) - Vector3(0, 0, -1));
        return 0.5 * Vector3(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    ray.direction.normalize();
    t = 0.5*(ray.direction.y() + 1.0);
    return (1.0 - t)*Vector3(1.0, 1.0, 1.0)+ t*Vector3(0.5, 0.7, 1.0);
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
        // This is the implementation of the 3 documents : Raytracing in a Week-end, the next week-end, and te rest of your life by Peter Shirley
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
