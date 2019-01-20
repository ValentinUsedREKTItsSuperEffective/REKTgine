#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"

struct HitRecord {
    float t;
    Vector3 p;
    Vector3 normal;
};

class Hitable {
    public:
        virtual bool hit(const Ray& ray, float tmin, float tmax, HitRecord& record) const = 0;
};

#endif // HITABLE_H
