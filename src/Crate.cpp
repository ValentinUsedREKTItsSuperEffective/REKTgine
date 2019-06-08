#include "Crate.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Crate::Crate(float dim, BaseMaterial *mat, std::string textureSrc) : Cube(dim, mat), _texture(textureSrc)
{
    _texture.load();
}

Crate::~Crate()
{
    //dtor
}
