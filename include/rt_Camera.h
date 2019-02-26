#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#define M_PI 3.14159265358979323846

#include "Ray.h"

double frand(){
    return double(rand()) / double(RAND_MAX);
}

Vector3 randomInUnitDisk(){
    Vector3 p;
    do{
        p = 2.0*Vector3(frand(), frand(),0) - Vector3(1,1,0);
    }while(p.dot(p) >= 1);

    return p;
}

class rt_Camera {
    public:
        rt_Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 up, float fov, float aspect, float aperture, float focusDist){
            lensRadius = aperture / 2;
            Vector3 u, v, w;
            double theta = fov * M_PI / 180.0;
            float halfHeight = tan(theta/2);
            float halfWidth = halfHeight * aspect;
            origin = lookFrom;
            w = normalize(lookFrom - lookAt);
            u = normalize(up.cross(w));
            v = w.cross(u);
            lowerLeftCorner = origin - halfWidth*focusDist*u - halfHeight*focusDist*v - focusDist*w;
            horizontal = 2*halfWidth*focusDist*u;
            vertical = 2*halfHeight*focusDist*v;
        }

        Ray getRay(float u, float v){
            Vector3 rd = lensRadius*randomInUnitDisk();
            Vector3 offset = u * rd.x() + v*rd.y();
            return Ray(origin + offset, lowerLeftCorner + u*horizontal + v*vertical - origin - offset);
        }

        Vector3 lowerLeftCorner;
        Vector3 horizontal;
        Vector3 vertical;
        Vector3 origin;
        float lensRadius;
};

#endif // RT_CAMERA_H
