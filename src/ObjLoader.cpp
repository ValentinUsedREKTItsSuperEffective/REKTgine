#include "ObjLoader.h"

#include <iostream>
#include <stdio.h>
#include <cstring>

ObjLoader::ObjLoader(){}

ObjLoader::~ObjLoader(){}

bool ObjLoader::load(std::string path, std::vector<glm::vec3> &verticesOut, std::vector<glm::vec2> &uvsOut, std::vector<glm::vec3> &normalsOut){
    std::vector<unsigned int> verticesIndex, uvsIndex, normalsIndex;
    std::vector<glm::vec3> tmp_vertices, tmp_normals;
    std::vector<glm::vec2> tmp_uvs;

    FILE * file = fopen(path.c_str(), "r");
    if(!file){
        std::cout<<"Error : Cannot find " << path << std::endl;
        return false;
    }

    while(!feof(file)){
        char header[256];
        fscanf(file, "%s", header);

        if(strcmp("v",header) == 0){ // vertices
            glm::vec3 vertex;
            fscanf(file,"%f" "%f" "%f\n", &vertex.x, &vertex.y, &vertex.z);
            tmp_vertices.push_back(vertex);
        } else if(strcmp("vt",header) == 0){ // uv
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            tmp_uvs.push_back(uv);
        } else if(strcmp("vn",header) == 0){ // normal
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            tmp_normals.push_back(normal);
        } else if(strcmp("f",header) == 0){ // face
            int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            if(matches != 9){
                std::cout << "Wrong data format !" << std::endl;
                return false;
            }

            verticesIndex.push_back(vertexIndex[0]);
            verticesIndex.push_back(vertexIndex[1]);
            verticesIndex.push_back(vertexIndex[2]);
            uvsIndex.push_back(uvIndex[0]);
            uvsIndex.push_back(uvIndex[1]);
            uvsIndex.push_back(uvIndex[2]);
            normalsIndex.push_back(normalIndex[0]);
            normalsIndex.push_back(normalIndex[1]);
            normalsIndex.push_back(normalIndex[2]);
        }
    }

    fclose(file);

    for(std::vector<unsigned int>::iterator it = verticesIndex.begin(); it != verticesIndex.end(); ++it){
        verticesOut.push_back(tmp_vertices.at((*it)-1));
    }

    for(std::vector<unsigned int>::iterator it = uvsIndex.begin(); it != uvsIndex.end(); ++it){
        uvsOut.push_back(tmp_uvs.at((*it)-1));
    }

    for(std::vector<unsigned int>::iterator it = normalsIndex.begin(); it != normalsIndex.end(); ++it){
        normalsOut.push_back(tmp_normals.at((*it)-1));
    }

}
