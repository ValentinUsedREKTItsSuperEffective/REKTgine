#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader
{
    public:
        Shader(std::string, std::string);
        ~Shader();
        bool load();
        bool compile(GLuint &shader, GLenum type, std::string const &fileSrc);
        GLuint getProgramID() const;

    private:
        GLuint _programID;
        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;

        std::string _vertexSource;
        std::string _fragmentSource;
};

#endif // SHADER_H
