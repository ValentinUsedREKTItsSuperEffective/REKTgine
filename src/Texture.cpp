#include "Texture.h"

Texture::Texture() : _ID(0), _textureSrc(""){

}

Texture::Texture(std::string src) : _ID(0), _textureSrc(src){

}

Texture::Texture(const Texture &texture){
    _textureSrc = texture._textureSrc;
    load();
}

Texture::~Texture(){
    glDeleteTextures(1,&_ID);
}

Texture& Texture::operator=(Texture const &texture){
    _textureSrc = texture._textureSrc;
    load();

    return *this;
}

bool Texture::load(){

    SDL_Surface* img = IMG_Load(_textureSrc.c_str());
    if(img == 0){
        std::cout << "Error : " << SDL_GetError() << std::endl;
        return false;
    }

    img = invertPixels(img);

    if(glIsTexture(_ID) == GL_TRUE)
        glDeleteTextures(1,&_ID);

    // ID generation
    glGenTextures(1,&_ID);

    // lock the texture
    glBindTexture(GL_TEXTURE_2D,_ID);

    // rgb or rgba
    GLenum internalFormat(0);

    // rgb or brg (.bmp)
    GLenum format(0);

    if(img->format->BytesPerPixel == 3){
        internalFormat = GL_RGB;

        if(img->format->Rmask == 0xff){
            format = GL_RGB;
        }
        else{
            format = GL_BGR;
        }
    }
    else if(img->format->BytesPerPixel == 4){
        internalFormat = GL_RGBA;

        if(img->format->Rmask == 0xff){
            format = GL_RGBA;
        }
        else{
            format = GL_BGRA;
        }
    }
    else{
        std::cout << "Error : Unknown format file !"<< std::endl;
        SDL_FreeSurface(img);
        return false;
    }

    // fill the texture
    glTexImage2D(GL_TEXTURE_2D,0,internalFormat,img->w,img->h,0,format,GL_UNSIGNED_BYTE,img->pixels);

    // filters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    // unlock
    glBindTexture(GL_TEXTURE_2D,0);

    SDL_FreeSurface(img);
    return true;
}

GLuint Texture::getID() const{
    return _ID;
}

void Texture::setSource(const std::string &src){
    _textureSrc = src;
}

SDL_Surface* Texture::invertPixels(SDL_Surface* img) const{
    int height = img->h;
    int width = img->w;
    int bytesPerPixels = img->format->BytesPerPixel;

    SDL_Surface* invertedImg = SDL_CreateRGBSurface(0,width,height,img->format->BitsPerPixel,
        img->format->Rmask,img->format->Gmask,img->format->Bmask,img->format->Amask);

    unsigned char* pixelsSrc = (unsigned char *)img->pixels;
    unsigned char* pixelsDest = (unsigned char *)invertedImg->pixels;

    for(int i = 0; i<height; i++)
        for(int j = 0; j<width * bytesPerPixels; j++)
            pixelsDest[width * bytesPerPixels * i + j] = pixelsSrc[width * bytesPerPixels * (height - i - 1) + j];

    return invertedImg;
}
