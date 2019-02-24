#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#define M_PI 3.14159265358979323846

#include "Ray.h"

class rt_Camera {
    public:
        rt_Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 up, float fov, float aspect){
            Vector3 u, v, w;
            double theta = fov * M_PI / 180.0;
            float halfHeight = tan(theta/2);
            float halfWidth = halfHeight * aspect;
            origin = lookFrom;
            w = normalize(lookFrom - lookAt);
            u = normalize(up.cross(w));
            v = w.cross(u);
            lowerLeftCorner = origin - halfWidth*u - halfHeight*v - w;;
            horizontal = 2*halfWidth*u;
            vertical = 2*halfHeight*v;
        }

        Ray getRay(float u, float v){
            return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
        }

        Vector3 lowerLeftCorner;
        Vector3 horizontal;
        Vector3 vertical;
        Vector3 origin;
};

#endif // RT_CAMERA_H
