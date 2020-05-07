#include "MTLLoader.hpp"

#include <iostream>
#include <cstring>

MTLLoader::MTLLoader(){}

MTLLoader::~MTLLoader(){}

bool MTLLoader::Load(std::string folderPath, std::string filename, MaterialParamaters &parameter){ // path, filename
    std::string path = folderPath + filename;
    FILE * file = fopen(path.c_str(), "r");
    if(!file){
        std::cout << "Error : Cannot find " << path << std::endl;
        return false;
    }

    while(!feof(file)){
        char header[256];
        fscanf(file, "%s", header);

        if(strcmp("Ns", header) == 0){
            fscanf(file, "%f\n", &parameter.shininess);
        } else if(strcmp("Ka", header) == 0){
            fscanf(file, "%f" "%f" "%f\n", &parameter.ambient.x, &parameter.ambient.y, &parameter.ambient.z);
        } else if(strcmp("Kd", header) == 0){
            fscanf(file, "%f" "%f" "%f\n", &parameter.color.x, &parameter.color.y, &parameter.color.z);
        } else if(strcmp("Ks", header) == 0){
            fscanf(file, "%f" "%f" "%f\n", &parameter.specular.x, &parameter.specular.y, &parameter.specular.z);
        } else if(strcmp("map_Kd", header) == 0){
            char s[100];
            fscanf(file, "%s\n", s);
            parameter.textureSrc = folderPath + std::string(s);
        } else if(strcmp("map_Ks", header) == 0){
            char s[100];
            fscanf(file, "%s\n", s);
            parameter.specularMapSrc = folderPath + std::string(s);
        }
    }

    return true;
}
