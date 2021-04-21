#ifndef RAYTRACER_BBOX_H
#define RAYTRACER_BBOX_H

#include "Vector3D.h"
#include "constants.h"


class Ray;

class BBox
{
public:
    BBox() = default;

    BBox(const Vector3D& p, const Vector3D& P);

    BBox(FLOAT x0, FLOAT y0, FLOAT z0,
         FLOAT x1, FLOAT y1, FLOAT z1);

    bool hit(const Ray& ray) const;

    FLOAT getSmall(Plane p) const {
        return ((FLOAT*)this)[p];
    }

    FLOAT getBig(Plane p) const {
        return ((FLOAT*)this)[p+3];
    }

    FLOAT& getSmall(Plane p){
        return ((FLOAT*)this)[p];
    }

    FLOAT& getBig(Plane p){
        return ((FLOAT*)this)[p+3];
    }

    bool clipRay(const Ray& ray, FLOAT& t_near, FLOAT& t_far) const;

    friend bool overlapping(const BBox& a, const BBox& b);

private:
    FLOAT x0, y0, z0;  // small point
    FLOAT x1, y1, z1;  // big point
};

bool overlapping(const BBox& a, const BBox& b);


#endif //RAYTRACER_BBOX_H
