#ifndef CRATE_H
#define CRATE_H

#include "Cube.h"
#include "Texture.h"

class Crate : public Cube
{
    public:
        Crate(float dim, BaseMaterial *material, std::string textureSrc);
        ~Crate();

    private:
        Texture _texture;
};

#endif // CRATE_H
