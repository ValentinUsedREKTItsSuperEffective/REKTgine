#include "Sprite.hpp"

Sprite::Sprite(string src) : Mesh(new SpriteGeometry(), new BaseMaterial(MaterialParamaters(src))){}

Sprite::~Sprite(){
    delete geometry;
    delete material;
}
