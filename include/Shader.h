#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

using namespace glm;

class Shader{
    public:
        GLuint programID;

        Shader(std::string, std::string);
        ~Shader();
        bool load();

        void bindFloat(const std::string &location, float f) const;
        void bindInt(const std::string &location, int i) const;
        void bindFloat3(const std::string &location, vec3 f) const;
        void bindMat4(const std::string &location, mat4 m) const;

    private:
        GLuint vertShaderID;
        GLuint fragShaderID;

        std::string vertSrc;
        std::string fragSrc;

        bool compile(GLuint &shader, GLenum type, std::string const &fileSrc);
};

#endif // SHADER_H
