#include "SpriteGeometry.hpp"

SpriteGeometry::SpriteGeometry(float spriteSize){
    spriteSize *= .5f;

    positions = {
        -spriteSize, -spriteSize, 0.f,
         spriteSize, -spriteSize, 0.f,
         spriteSize,  spriteSize, 0.f,
        -spriteSize,  spriteSize, 0.f
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

    indexes = {
        0, 1, 2,
        2, 3, 0
    };

    load();
}

SpriteGeometry::~SpriteGeometry(){}
