#include "Texture.h"

Texture::Texture() : textureID(0), colorByDefault(glm::vec3(1.0f)), inverseImage(true), src(""), width(1), height(1){}

Texture::Texture(GLsizei width, GLsizei height) : textureID(0), colorByDefault(glm::vec3(1.0f)), inverseImage(true), src(""), width(width), height(height){}

Texture::Texture(std::string src) : textureID(0), colorByDefault(glm::vec3(1.0f)), inverseImage(true), src(src), width(1), height(1){}

Texture::Texture(const Texture &texture) : colorByDefault(glm::vec3(1.0f)), width(1), height(1){
    src = texture.src;
    inverseImage = texture.inverseImage;
    load();
}

Texture::~Texture(){
    glDeleteTextures(1, &textureID);
}

Texture& Texture::operator=(Texture const &texture){
    src = texture.src;
    load();

    return *this;
}

bool Texture::load(){
    if(glIsTexture(textureID) == GL_TRUE)
        glDeleteTextures(1, &textureID);

    // ID generation
    glGenTextures(1, &textureID);

    // lock the texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // rgb or rgba
    GLenum internalFormat = GL_RGB;

    // rgb or brg (.bmp)
    GLenum format = GL_RGB;

    GLvoid *data;

    SDL_Surface* img = NULL;

    if(src != ""){
        img = IMG_Load(src.c_str());
        if(img == 0){
            std::cout << "Error : " << SDL_GetError() << std::endl;
            return false;
        }

        if(inverseImage){
            img = invertPixels(img);
        }

        if(img->format->BytesPerPixel == 3){
            internalFormat = GL_RGB;

            if(img->format->Rmask == 0xff){
                format = GL_RGB;
            } else {
                format = GL_BGR;
            }
        } else if(img->format->BytesPerPixel == 4){
            internalFormat = GL_RGBA;

            if(img->format->Rmask == 0xff){
                format = GL_RGBA;
            } else{
                format = GL_BGRA;
            }
        } else {
            std::cout << "Error : Unknown format file !"<< std::endl;
            SDL_FreeSurface(img);
            return false;
        }

        width = img->w;
        height = img->h;

        data = img->pixels;
    } else {
        img = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

        if(img == NULL){
            std::cout << "SDL_CreateRGBSurface() failed: " << SDL_GetError()<< std::endl;
            SDL_FreeSurface(img);
            return false;
        }

        SDL_LockSurface(img);
        SDL_FillRect(img, NULL, SDL_MapRGB(img->format, colorByDefault.x * 255, colorByDefault.y * 255, colorByDefault.z * 255));
        SDL_UnlockSurface(img);

        data = img->pixels;
    }

    // fill the texture
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // unlock
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(img);
    return true;
}

SDL_Surface* Texture::invertPixels(SDL_Surface* img) const {
    int height = img->h;
    int width = img->w;
    int bytesPerPixels = img->format->BytesPerPixel;

    SDL_Surface* invertedImg = SDL_CreateRGBSurface(0, width,height, img->format->BitsPerPixel,
        img->format->Rmask, img->format->Gmask, img->format->Bmask, img->format->Amask);

    unsigned char* pixelsSrc = (unsigned char *)img->pixels;
    unsigned char* pixelsDest = (unsigned char *)invertedImg->pixels;

    for(int i = 0; i<height; i++)
        for(int j = 0; j<width * bytesPerPixels; j++)
            pixelsDest[width * bytesPerPixels * i + j] = pixelsSrc[width * bytesPerPixels * (height - i - 1) + j];

    return invertedImg;
}
