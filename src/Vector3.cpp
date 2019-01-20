#include "Vector3.h"

inline Vector3& Vector3::operator-=(const Vector3& vec){
    v[0] -= vec[0];
    v[1] -= vec[1];
    v[2] -= vec[2];
    return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& vec){
    v[0] *= vec[0];
    v[1] *= vec[1];
    v[2] *= vec[2];
    return *this;
}

inline Vector3 operator/(const Vector3& v1, const Vector3& v2){
    return Vector3(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

inline Vector3& Vector3::operator/=(const Vector3& vec){
    v[0] /= vec[0];
    v[1] /= vec[1];
    v[2] /= vec[2];
    return *this;
}

inline Vector3& Vector3::operator*=(double t){
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}

inline Vector3 operator/(const Vector3& v, float f){
    return Vector3(v[0] / f, v[1] / f, v[2] / f);
}

inline double Vector3::dot(const Vector3& vec){
    return v[0]*vec[0] + v[1]*vec[1] + v[2]*vec[2];
}

inline Vector3 Vector3::cross(const Vector3& vec){
    return Vector3(
        v[1]*vec[2] - v[2]*vec[1],
        -v[0]*vec[2] - v[2]*vec[0],
        v[0]*vec[1] - v[1]*vec[0]
    );
}
