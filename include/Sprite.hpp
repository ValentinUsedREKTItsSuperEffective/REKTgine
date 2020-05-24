#ifndef SPRITE_H
#define SPRITE_H

#include<string>

#include "Object3D.h"
#include "Mesh.hpp"
#include "PlaneGeometry.hpp"
#include "Materials/BaseMaterial.hpp"

using namespace std;

class Sprite : public Mesh {
    public:
        Sprite(string src);
        virtual ~Sprite();
};

#endif // SPRITE_H
