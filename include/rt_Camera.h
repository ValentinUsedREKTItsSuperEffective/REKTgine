#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "Ray.h"

class rt_Camera {
    public:
        rt_Camera() {
            lowerLeftCorner = Vector3(-2.0, -1.0, -1.0);
            cameraLens = Vector3(4.0, 2.0, 0.0);
            origin = Vector3(0.0, 0.0, 0.0);
        }

        Ray getRay(Vector3 uv){
            return Ray(origin, lowerLeftCorner + uv*cameraLens - origin);
        }

        Vector3 lowerLeftCorner;
        Vector3 cameraLens;
        Vector3 origin;
};

#endif // RT_CAMERA_H
