#ifndef MTLLOADER_H
#define MTLLOADER_H

#include <string>

#include "MaterialParamaters.hpp"

class MTLLoader
{
    public:
        MTLLoader();
        virtual ~MTLLoader();
        bool Load(std::string folderPath, std::string filename, MaterialParamaters &parameter);
};

#endif // MTLLOADER_H
