#ifndef RAYTRACER_AMBIENT_H
#define RAYTRACER_AMBIENT_H

#include "Light.h"
#include "Color.h"
#include "Vector3D.h"


class Ambient : public Light
{
public:
    Ambient(const Color& c, FLOAT ls);
    Ambient(FLOAT r, FLOAT g, FLOAT b, FLOAT ls);

    Vector3D get_direction(const ShadeRec& sr);

    Color L(const ShadeRec& sr);

    bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
private:
    FLOAT ls;      // power
    Color color;    // color
    Vector3D o;     // position
};

#endif //RAYTRACER_AMBIENT_H
