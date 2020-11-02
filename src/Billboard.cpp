#include "Billboard.hpp"

Billboard::Billboard(string src, Camera* cam) : Sprite(src), camera(cam){}

Billboard::~Billboard(){}

void Billboard::display(mat4 &projection, mat4 &modelView){
    LookAt(*camera);
    Sprite::display(projection, modelView);
}
