#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Mesh.hpp"

using namespace glm;
using namespace std;

struct FaceTriplet {
    int positionIndex;
    int uvIndex;
    int normalIndex;
};

class ObjLoader{
    public:
        ObjLoader();
        ~ObjLoader();
        bool load(string path, Mesh &mesh);
};

#endif // OBJLOADER_H
