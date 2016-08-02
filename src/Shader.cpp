#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader(std::string vertexSource, std::string fragmentSource) : _programID(0), _vertexShaderID(0), _fragmentShaderID(0),
                                                                        _vertexSource(vertexSource), _fragmentSource(fragmentSource)
{
}

Shader::~Shader()
{
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
    glDeleteProgram(_programID);
}

bool Shader::load(){

    if(compile(_vertexShaderID,GL_VERTEX_SHADER,_vertexSource) == false)
    {
        return false;
    }

    if(compile(_fragmentShaderID,GL_FRAGMENT_SHADER,_fragmentSource) == false)
    {
        return false;
    }

    _programID = glCreateProgram();

    glAttachShader(_programID,_vertexShaderID);
    glAttachShader(_programID,_fragmentShaderID);

    glBindAttribLocation(_programID,0,"in_Vertex");
    glBindAttribLocation(_programID,1,"in_Color");
    glBindAttribLocation(_programID,2,"in_TexCoord0");

    glLinkProgram(_programID);

    return true;
}

bool Shader::compile(GLuint &shader, GLenum type, std::string const &fileSrc){

    shader = glCreateShader(type);

    std::ifstream file(fileSrc.c_str());
    if(!file){
        std::cout<<"Error : Cannot find " << fileSrc << std::endl;
        glDeleteShader(shader);
        return false;
    }

    std::string line, srcCode;

    while(getline(file,line))
        srcCode += line + "\n";

    file.close();

    const GLchar* charSrcCode = srcCode.c_str();

    glShaderSource(shader,1,&charSrcCode,0);

    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success){
        GLint lengthLog = 0;
        glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&lengthLog);

        char* log = new char[lengthLog + 1];
        glGetShaderInfoLog(shader,lengthLog,&lengthLog,log);
        log[lengthLog] = '\0';

        std::cout << log << std::endl;

        delete[] log;
        glDeleteShader(shader);
        return false;
    }

    return true;
}

GLuint Shader::getProgramID() const{

    return _programID;
}
