#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "Vector3D.h"
#include "Color.h"
#include "constants.h"

struct ShadeRec;
struct Ray;
class BBox;
class Material;
class Ray;


class Triangle
{
public:
//    Triangle() = default;

    explicit Triangle(const Vector3D &v0, const Vector3D &v1, const Vector3D &v2);

    Triangle(const Triangle&);

    Triangle(const Triangle&&);

    Triangle& operator=(const Triangle&);

    bool hit_object(const Ray& ray, FLOAT& tmin, ShadeRec& sr);

    bool hit_object(const Ray& ray, ShadeRec& sr);

    bool shadow_hit(const Ray& ray, FLOAT& tmin) const;

    BBox get_BBox() const;

public:
    inline static unsigned idgen = 0;
    unsigned id;
    Vector3D v0,v1,v2;
    Color c;
//    Vector3D hitbyDir;
//    Material* material{nullptr};
};


#endif //RAYTRACER_TRIANGLE_H
