#ifndef MATERIAL_RT_H
#define MATERIAL_RT_H

Vector3 getPointInUnitSphere();

class Material_RT {
    public:
        virtual bool scatter(const Ray& in, const HitRecord& record, Vector3& attenuation, Ray& scattered) const = 0;
};

class Lambertian_RT : public Material_RT {
    public:
        Vector3 albedo;

        Lambertian_RT(const Vector3& a) : albedo(a){}
        virtual bool scatter(const Ray& in, const HitRecord& record, Vector3& attenuation, Ray& scattered) const {
            Vector3 p = record.p + record.normal + getPointInUnitSphere();
            scattered = Ray(record.p, p - record.p);
            attenuation = albedo;
            return true;
        }
};

class Metal_RT : public Material_RT {
    public:
        Vector3 albedo;
        float fuzzy;

        Metal_RT(const Vector3& a, float f) : albedo(a), fuzzy(f){}
        virtual bool scatter(const Ray& in, const HitRecord& record, Vector3& attenuation, Ray& scattered) const {
            Vector3 reflected = reflect(normalize(in.direction), record.normal);
            scattered = Ray(record.p, reflected + fuzzy*getPointInUnitSphere());
            attenuation = albedo;
            return scattered.direction.dot(record.normal) > 0;
        }
};

#endif // MATERIAL_RT_H
