#include <math.h>

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
    public:
        Vector3() {}
        Vector3(double x, double y, double z) {v[0] = x; v[1] = y; v[2] = z;}

        inline double x() const {return v[0];}
        inline double y() const {return v[1];}
        inline double z() const {return v[2];}
        inline double r() const {return v[0];}
        inline double g() const {return v[1];}
        inline double b() const {return v[2];}

        inline const Vector3& operator+() const {return *this;}
        inline Vector3 operator-() {return Vector3(-v[0], -v[1], -v[2]);}
        inline double operator[](int i) const {return v[i];}
        inline double& operator[](int i) {return v[i];}

        inline Vector3& operator+=(const Vector3&);
        inline Vector3& operator-=(const Vector3&);
        inline Vector3& operator*=(const Vector3&);
        inline Vector3& operator/=(const Vector3&);
        inline Vector3& operator*=(double);
        inline Vector3& operator/=(double);

        inline float length() const {return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);}
        inline float lengthSq() const {return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];}
        inline void normalize();
        inline double dot(const Vector3& vec);
        inline Vector3 cross(const Vector3& vec);

        double v[3];
};

inline Vector3 operator+(const Vector3& v1, const Vector3& v2){
    return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline Vector3 operator*(const Vector3& v1, const Vector3& v2){
    return Vector3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline Vector3 operator*(float f, const Vector3& v){
    return Vector3(v[0] * f, v[1] * f, v[2] * f);
}

inline Vector3 operator*(const Vector3& v, float f){
    return Vector3(v[0] * f, v[1] * f, v[2] * f);
}

inline void Vector3::normalize(){
    double k = 1 / length();
    v[0] *= k;
    v[1] *= k;
    v[2] *= k;
}

#endif // VECTOR3_H
