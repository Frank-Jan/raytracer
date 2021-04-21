#ifndef RAYTRACER_AREALIGHT_H
#define RAYTRACER_AREALIGHT_H

#include "Light.h"
#include "Vector3D.h"

class Triangle;
class Material;

class AreaLight : public Light
{
public:
    AreaLight();
    AreaLight(Triangle*);

    ~AreaLight();

    virtual Vector3D get_direction(const ShadeRec& sr);

    virtual Color L(const ShadeRec& sr);

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

    virtual FLOAT G(const ShadeRec& sr);

    virtual FLOAT pdf(ShadeRec& sr);

public:
    Triangle* obj;
    Material* material;     // an emissive material
    Vector3D sample_point;   // sample point on the surface
    Vector3D normal;        // normal at the sample point
    Vector3D wi;            // unit vector from hit point to sample point
};


#endif //RAYTRACER_AREALIGHT_H
