#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader{
    public:
        GLuint programID;

        Shader();
        Shader(std::string, std::string);
        ~Shader();
        bool load();
        bool compile(GLuint &shader, GLenum type, std::string const &fileSrc);
        GLuint getProgramID() const;

    private:
        GLuint vertShaderID;
        GLuint fragShaderID;

        std::string vertSrc;
        std::string fragSrc;
};

#endif // SHADER_H
