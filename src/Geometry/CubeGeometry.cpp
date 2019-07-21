#include "Geometry/CubeGeometry.h"

CubeGeometry::CubeGeometry(float cubeSize){
    cubeSize *= 0.5f;

    positions = {
        -cubeSize, -cubeSize, -cubeSize,
         cubeSize, -cubeSize, -cubeSize,
         cubeSize,  cubeSize, -cubeSize,
         cubeSize,  cubeSize, -cubeSize,
        -cubeSize,  cubeSize, -cubeSize,
        -cubeSize, -cubeSize, -cubeSize,

        -cubeSize, -cubeSize,  cubeSize,
         cubeSize, -cubeSize,  cubeSize,
         cubeSize,  cubeSize,  cubeSize,
         cubeSize,  cubeSize,  cubeSize,
        -cubeSize,  cubeSize,  cubeSize,
        -cubeSize, -cubeSize,  cubeSize,

        -cubeSize,  cubeSize,  cubeSize,
        -cubeSize,  cubeSize, -cubeSize,
        -cubeSize, -cubeSize, -cubeSize,
        -cubeSize, -cubeSize, -cubeSize,
        -cubeSize, -cubeSize,  cubeSize,
        -cubeSize,  cubeSize,  cubeSize,

         cubeSize,  cubeSize,  cubeSize,
         cubeSize,  cubeSize, -cubeSize,
         cubeSize, -cubeSize, -cubeSize,
         cubeSize, -cubeSize, -cubeSize,
         cubeSize, -cubeSize,  cubeSize,
         cubeSize,  cubeSize,  cubeSize,

        -cubeSize, -cubeSize, -cubeSize,
         cubeSize, -cubeSize, -cubeSize,
         cubeSize, -cubeSize,  cubeSize,
         cubeSize, -cubeSize,  cubeSize,
        -cubeSize, -cubeSize,  cubeSize,
        -cubeSize, -cubeSize, -cubeSize,

        -cubeSize,  cubeSize, -cubeSize,
         cubeSize,  cubeSize, -cubeSize,
         cubeSize,  cubeSize,  cubeSize,
         cubeSize,  cubeSize,  cubeSize,
        -cubeSize,  cubeSize,  cubeSize,
        -cubeSize,  cubeSize, -cubeSize
    };

    normals = {
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,

        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,

        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,

        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f
    };

    uvs = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };

    load();
}

CubeGeometry::~CubeGeometry(){}
