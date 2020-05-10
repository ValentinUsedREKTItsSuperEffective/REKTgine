#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Texture{
    public:
        GLuint textureID;
        glm::vec3 colorByDefault;
        bool inverseImage;

        Texture();
        Texture(std::string src);
        Texture(const Texture &texture);
        ~Texture();
        Texture& operator=(Texture const &texture);
        bool load();
        SDL_Surface* invertPixels(SDL_Surface *img) const;

    private:
        std::string src;
};

#endif // TEXTURE_H
