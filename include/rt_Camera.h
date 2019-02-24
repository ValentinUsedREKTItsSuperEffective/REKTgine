#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#define M_PI 3.14159265358979323846

#include "Ray.h"

class rt_Camera {
    public:
        rt_Camera(float fov, float aspect) {
            double theta = fov * M_PI / 180.0;
            float halfHeight = tan(theta/2);
            float halfWidth = halfHeight * aspect;
            lowerLeftCorner = Vector3(-halfWidth, -halfHeight, -1.0);
            cameraLens = Vector3(2*halfWidth, 2*halfHeight, 0.0);
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
