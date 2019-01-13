#include "Vector3.h"

#ifndef RAY_H
#define RAY_H


class Ray{
    public:
        Vector3 origin;
        Vector3 direction;

        Ray();
        Ray(const Vector3& o, const Vector3& d){origin = o; direction = d;}
        Vector3 projectAt(float t) const {return origin + t*direction;}
};

#endif // RAY_H
