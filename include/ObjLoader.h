#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

class ObjLoader
{
    public:
        ObjLoader();
        ~ObjLoader();
        bool load(std::string path, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals);

        private:
};

#endif // OBJLOADER_H
