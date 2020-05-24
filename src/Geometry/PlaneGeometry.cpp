#include "PlaneGeometry.hpp"

PlaneGeometry::PlaneGeometry(float planeSize){
    planeSize *= 0.5f;

    positions = {
        -planeSize,  0.f, -planeSize,
         planeSize,  0.f, -planeSize,
         planeSize,  0.f,  planeSize,
        -planeSize,  0.f,  planeSize
    };

    normals = {
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f
    };

    uvs = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };

    indexes = {
        0, 1, 2,
        2, 3, 0
    };

    load();
}

PlaneGeometry::~PlaneGeometry(){}

void PlaneGeometry::SetAsSpriteGeometry(){
    float planeSize = positions[1];

    positions = {
        -planeSize, -planeSize, 0.f,
         planeSize, -planeSize, 0.f,
         planeSize,  planeSize, 0.f,
        -planeSize,  planeSize, 0.f
    };

    normals = {
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f
    };

    uvs = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    load();
}
