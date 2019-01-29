#ifndef RT_SPHERE_H
#define RT_SPHERE_H

#include "Hitable.h"

class rt_Sphere : public Hitable {
    public:
        rt_Sphere() {}
        rt_Sphere(Vector3 c, float r, Material_RT* mat) : center(c), radius(r), material(mat) {};
        virtual bool hit(const Ray& ray, float tmin, float tmax, HitRecord& record) const;

        Vector3 center;
        float radius;
        Material_RT* material;
};

bool rt_Sphere::hit(const Ray& ray, float tmin, float tmax, HitRecord& record) const {
    Vector3 oc = ray.origin - center;
    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - radius*radius;
    float det = b*b - a*c;
    if(det > 0){
        float t = (-b - sqrt(det)) / a;
        if (tmin < t && tmax > t) {
            record.t = t;
            record.p = ray.projectAt(t);
            record.normal = normalize(record.p - center);
            record.material = material;
            return true;
        }

        t = (-b + sqrt(det)) / a;
        if (tmin < t && tmax > t) {
            record.t = t;
            record.p = ray.projectAt(t);
            record.normal = normalize(record.p - center);
            record.material = material;
            return true;
        }
    }

    return false;
}

#endif // RT_SPHERE_H
