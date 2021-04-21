#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

#include "Light.h"
#include "Color.h"
#include "Vector3D.h"

class PointLight : public Light
{
public:
    PointLight(const Vector3D& location=Vector3D(), const Color& c=Color(1.0), FLOAT ls=1.0);
    PointLight(const Vector3D& location, FLOAT r, FLOAT g, FLOAT b, FLOAT ls=1.0);

    void set_radiance(FLOAT _ls) {
        ls = _ls;
    }

    Vector3D get_direction(const ShadeRec& sr);

    Color L(const ShadeRec& sr);

    bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:
    FLOAT ls;      // power
    Color color;    // color
    Vector3D o;     // position
};


#endif //RAYTRACER_POINTLIGHT_H
