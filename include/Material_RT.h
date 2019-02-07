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

class Dielectric_RT: public Material_RT {
    public:
        float refractionIndex;

        Dielectric_RT(float r): refractionIndex(r) {}
        virtual bool scatter(const Ray& in, const HitRecord& record, Vector3& attenuation, Ray& scattered) const {
            Vector3 outwardNormal;
            Vector3 reflected = reflect(normalize(in.direction), record.normal);
            float ni_over_nt;
            attenuation = Vector3(1.0, 1.0, 1.0);
            Vector3 refracted;
            float reflectedProb, cosine;
            if(dot(in.direction, record.normal) > 0.0){
                outwardNormal = -record.normal;
                ni_over_nt = refractionIndex;
                cosine = refractionIndex * dot(in.direction, record.normal) / in.direction.length();
            } else {
                outwardNormal = record.normal;
                ni_over_nt = 1.0 / refractionIndex;
                cosine = -dot(in.direction, record.normal) / in.direction.length();
            }

            if(refract(in.direction, outwardNormal, ni_over_nt, refracted)){
                reflectedProb = schlick(cosine, refractionIndex);
            } else {
                scattered = Ray(record.p, reflected);
                reflectedProb = 1;
            }

            if(frand() < reflectedProb){
                scattered = Ray(record.p, reflected);
            } else {
                scattered = Ray(record.p, refracted);
            }

            return true;
        }

        float schlick(float cosine, float refIdx) const {
            float r0 = (1 - refIdx) / (1 + refIdx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow(1 - cosine, 5);
        }

        double frand() const {
            return double(rand()) / double(RAND_MAX);
        }
};

#endif // MATERIAL_RT_H
