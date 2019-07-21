#ifndef CUBEGEOMETRY_H
#define CUBEGEOMETRY_H

#include <Geometry/Geometry.h>

class CubeGeometry : public Geometry {
    public:
        CubeGeometry(float cubeSize);
        virtual ~CubeGeometry();
};

#endif // CUBEGEOMETRY_H
