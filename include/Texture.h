#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Texture
{
    public:
        Texture();
        Texture(std::string src);
        Texture(const Texture &texture);
        ~Texture();
        Texture& operator=(Texture const &texture);
        bool load();
        GLuint getID() const;
        void setSource(const std::string &src);
        SDL_Surface* invertPixels(SDL_Surface *img) const;

    private:
        GLuint _ID;
        std::string _textureSrc;
};

#endif // TEXTURE_H
