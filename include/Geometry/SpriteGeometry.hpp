#ifndef SPRITEGEOMETRY_H
#define SPRITEGEOMETRY_H

#include <Geometry/Geometry.h>

class SpriteGeometry : public Geometry {
    public:
        SpriteGeometry(float spriteSize = 1.f);
        virtual ~SpriteGeometry();
};

#endif // SPRITEGEOMETRY_H
