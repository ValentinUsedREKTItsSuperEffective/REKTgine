#include "Sprite.hpp"

Sprite::Sprite(string src) : Mesh(new PlaneGeometry(), new BaseMaterial(MaterialParamaters(src))){

}

Sprite::~Sprite(){
    delete geometry;
    delete material;
}
