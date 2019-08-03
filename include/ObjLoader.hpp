#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Geometry/Geometry.h"

using namespace glm;

struct FaceTriplet {
    int positionIndex;
    int uvIndex;
    int normalIndex;
};

class ObjLoader{
    public:
        ObjLoader();
        ~ObjLoader();
        bool load(std::string path, Geometry &geometry);
};

#endif // OBJLOADER_H
