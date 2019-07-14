#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader() : programID(0), vertShaderID(0), fragShaderID(0), vertSrc(""), fragSrc(""){}

Shader::Shader(std::string vSrc, std::string fSrc) : programID(0), vertShaderID(0), fragShaderID(0), vertSrc(vSrc), fragSrc(fSrc){}

Shader::~Shader(){
    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);
    glDeleteProgram(programID);
}

bool Shader::load(){
    if(compile(vertShaderID ,GL_VERTEX_SHADER, vertSrc) == false){
        return false;
    }

    if(compile(fragShaderID,GL_FRAGMENT_SHADER,fragSrc) == false){
        return false;
    }

    programID = glCreateProgram();

    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    glLinkProgram(programID);

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

void Shader::bindFloat(const std::string &location, float f) const {
    glUniform1f(glGetUniformLocation(programID, location.c_str()), f);
}

void Shader::bindInt(const std::string &location, int i) const {
    glUniform1i(glGetUniformLocation(programID, location.c_str()), i);
}

void Shader::bindFloat3(const std::string &location, vec3 f) const {
    glUniform3fv(glGetUniformLocation(programID, location.c_str()), 1, value_ptr(f));
}
