#ifndef RAYTRACER_DIRECTIONAL_H
#define RAYTRACER_DIRECTIONAL_H

#include "Light.h"
#include "Color.h"
#include "Vector3D.h"


class Directional : public Light
{
public:
    Directional(const Vector3D& direction, const Color& c, FLOAT ls=1.0);
    Directional(const Vector3D& direction, FLOAT r, FLOAT g, FLOAT b, FLOAT ls=1.0);

    Vector3D get_direction(const ShadeRec& sr) const;

    Color L(const ShadeRec& sr) const;

    bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:
    FLOAT ls;      // power
    Color color;    // color
    Vector3D d;     // direction
};


#endif //RAYTRACER_DIRECTIONAL_H
