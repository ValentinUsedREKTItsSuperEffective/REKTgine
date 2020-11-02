#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "Sprite.hpp"
#include "Camera.h"

class Billboard : public Sprite {
    public:
        Billboard(string src, Camera* camera);
        virtual ~Billboard();

        virtual void display(mat4 &projection, mat4 &modelView);

    protected:
        Camera* camera;
};

#endif // BILLBOARD_H
