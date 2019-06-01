#ifndef CRATE_H
#define CRATE_H

#include "Cube.h"
#include "Texture.h"

class Crate : public Cube
{
    public:
        Crate(float dim, std::string vertexShader, std::string fragmentShader, std::string textureSrc);
        ~Crate();
        void display(glm::mat4 &projection, glm::mat4 &modelView);
        void load();

    private:
        Texture _texture;
};

#endif // CRATE_H
