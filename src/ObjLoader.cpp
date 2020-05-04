#include "ObjLoader.hpp"

#include <iostream>
#include <stdio.h>
#include <cstring>

ObjLoader::ObjLoader(){}

ObjLoader::~ObjLoader(){}

bool ObjLoader::load(string path, Mesh &mesh){
    vector<vec3> tmp_positions, tmp_normals;
    vector<vec2> tmp_uvs;
    vector<FaceTriplet> tmp_indexes;

    bool firstMesh = true;
    Mesh current = mesh;

    FILE * file = fopen(path.c_str(), "r");
    if(!file){
        cout << "Error : Cannot find " << path << endl;
        return false;
    }

    vec3 position, normal;
    vec2 uv;
    int positionIndex[3], uvIndex[3], normalIndex[3];
    while(!feof(file)){
        char header[256];
        fscanf(file, "%s", header);

        if(strcmp("o", header) == 0){
            if(firstMesh){
                firstMesh = false;
            } else {
                // TODO : create a new Mesh as child of mesh and set it current
            }
        } else if(strcmp("v", header) == 0){ // vertices
            fscanf(file, "%f" "%f" "%f\n", &position.x, &position.y, &position.z);
            tmp_positions.push_back(position);
        } else if(strcmp("vt", header) == 0){ // uv
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            tmp_uvs.push_back(uv);
        } else if(strcmp("vn", header) == 0){ // normal
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            tmp_normals.push_back(normal);
        } else if(strcmp("f", header) == 0){ // face
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &positionIndex[0], &uvIndex[0], &normalIndex[0], &positionIndex[1], &uvIndex[1], &normalIndex[1], &positionIndex[2], &uvIndex[2], &normalIndex[2]);

            if(matches != 9){
                cout << "Wrong data format !" << endl;
                return false;
            }

            for(int i = 0; i < 3; i++){
                int j = 0;
                int duplicateIndex = -1;
                while(duplicateIndex == -1 && j < tmp_indexes.size()){
                    if(tmp_indexes[j].positionIndex == positionIndex[i] && tmp_indexes[j].uvIndex == uvIndex[i] && tmp_indexes[j].normalIndex == normalIndex[i]){
                        duplicateIndex = j;
                    }

                    j++;
                }

                if(duplicateIndex == -1){
                    FaceTriplet f;
                    f.positionIndex = positionIndex[i];
                    f.uvIndex = uvIndex[i];
                    f.normalIndex = normalIndex[i];
                    tmp_indexes.push_back(f);
                    current.geometry->indexes.push_back(j);
                } else {
                    current.geometry->indexes.push_back(duplicateIndex);
                }
            }
        }
    }

    for(auto it = tmp_indexes.begin(); it < tmp_indexes.end(); it++){
        current.geometry->positions.push_back(tmp_positions[(*it).positionIndex - 1].x);
        current.geometry->positions.push_back(tmp_positions[(*it).positionIndex - 1].y);
        current.geometry->positions.push_back(tmp_positions[(*it).positionIndex - 1].z);

        current.geometry->normals.push_back(tmp_normals[(*it).normalIndex - 1].x);
        current.geometry->normals.push_back(tmp_normals[(*it).normalIndex - 1].y);
        current.geometry->normals.push_back(tmp_normals[(*it).normalIndex - 1].z);

        current.geometry->uvs.push_back(tmp_uvs[(*it).uvIndex - 1].x);
        current.geometry->uvs.push_back(tmp_uvs[(*it).uvIndex - 1].y);
    }

    fclose(file);

    current.geometry->load();

    return true;
}
