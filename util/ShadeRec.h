#ifndef RAYTRACER_SHADEREC_H
#define RAYTRACER_SHADEREC_H

#include "Ray.h"
#include "Vector3D.h"
#include "constants.h"

class Triangle;
class World;
class Material;

struct ShadeRec
{
    explicit ShadeRec(World* _w) : world(_w) { }
    ShadeRec(ShadeRec& sr) = default;
    ~ShadeRec() = default;

    World* world{nullptr};
    bool hit{false};
    Ray ray;
    FLOAT tmin = hugeValue;
    Vector3D normal;
    Vector3D hit_point;
    Triangle* triangle {nullptr};
    Material* material {nullptr};

};

#endif //RAYTRACER_SHADEREC_H
