#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "Color.h"
#include "constants.h"

class Vector3D;
class ShadeRec;
class Point3D;
class Ray;

class Light
{
public:
    explicit Light(bool _shadows = true) :
    shadows(_shadows) { };

    virtual ~Light() = default;

    virtual Vector3D get_direction(const ShadeRec& sr) = 0;

    virtual Color L(const ShadeRec& sr) = 0;

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const = 0;

    virtual FLOAT G(const ShadeRec& sr) { return 1.0; }

    virtual FLOAT pdf(ShadeRec& sr) { return 1.0; }

    bool casts_shadows() const { return shadows; }
protected:
    bool shadows;

};

#endif //RAYTRACER_LIGHT_H
