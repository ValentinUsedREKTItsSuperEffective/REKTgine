#ifndef MESH_H
#define MESH_H

#include "Object3D.h"
#include "Shader.h"
#include "Materials/BaseMaterial.h"
#include "Geometry/Geometry.h"

class Mesh : public Object3D {
     public:
        Mesh(Geometry *geometry, BaseMaterial *material);
        ~Mesh();
        virtual void display(mat4 &projection, mat4 &modelView);

        inline void useLight(Light &light){
            material->useLight(light);
        }

    protected:
        Geometry *geometry;
        BaseMaterial *material;
};

#endif // MESH_H
