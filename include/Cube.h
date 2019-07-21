#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"
#include "Shader.h"
#include "Materials/BaseMaterial.h"
#include "Geometry/Geometry.h"

class Cube : public Object3D {
    public:
        Cube(Geometry *geometry, BaseMaterial *material);
        ~Cube();
        virtual void display(mat4 &projection, mat4 &modelView);

        inline void useLight(Light &light){
            material->useLight(light);
        }

    protected:
        BaseMaterial *material;
        Geometry *geometry;
};

#endif // CUBE_H
