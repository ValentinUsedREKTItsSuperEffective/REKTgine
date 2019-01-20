#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "Hitable.h"

class HitableList : public Hitable {
    public:
        HitableList() {}
        HitableList(Hitable** l, int n) {list = l; size = n;}
        virtual bool hit(const Ray& ray, float tmin, float tmax, HitRecord& record) const;

        Hitable **list;
        int size;
};

bool HitableList::hit(const Ray& ray, float tmin, float tmax, HitRecord& record) const {
    HitRecord tmp;
    bool hitAnything = false;
    double closestSoFar = tmax;
    for(int i = 0; i < size; i++){
        if(list[i]->hit(ray, tmin, closestSoFar, tmp)){
            hitAnything = true;
            closestSoFar = tmp.t;
            record = tmp;
        }
    }

    return hitAnything;
}

#endif // HITABLELIST_H
