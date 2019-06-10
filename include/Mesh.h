#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ObjLoader.h"
#include "Shader.h"
#include "Texture.h"
#include "Lights/Light.h"

class Mesh
{
    public:
        Mesh(std::string objPath, std::string vertexShader, std::string fragmentShader);
        Mesh(std::string objPath, std::string vertexShader, std::string fragmentShader, std::string textureSrc);
        ~Mesh();
        void display(glm::mat4 &projection, glm::mat4 &modelView);
        void load();
        void updateVBO(void *data, int sizeBytes, int offset);
        void useLight(Light &light);

    private:
        std::vector<glm::vec3> _vertices;
        std::vector<glm::vec2> _uvs;
        std::vector<glm::vec3> _normals;

        ObjLoader _objLoader;
        Shader _shader;
        Texture _texture;

        GLuint _vbo;
        int _sizeVerticesBytes;
        int _sizeUvsBytes;
        int _sizeNormalsBytes;
        GLuint _vao;
};

#endif // SCENEOBJECT_H
