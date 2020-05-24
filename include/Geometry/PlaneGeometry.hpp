#ifndef PLANEGEOMETRRY_H
#define PLANEGEOMETRRY_H

#include <Geometry/Geometry.h>

class PlaneGeometry : public Geometry {
    public:
        PlaneGeometry(float planeSize = 1.f);
        virtual ~PlaneGeometry();

        void SetAsSpriteGeometry();
};

#endif // PLANEGEOMETRRY_H
