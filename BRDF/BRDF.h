#ifndef RAYTRACER_BRDF_H
#define RAYTRACER_BRDF_H
#include "Vector3D.h"

class Color;
class Sampler;
class ShadeRec;

class BRDF
{
public:
    virtual Color f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const = 0;

    virtual Color sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& w0) const = 0;

    virtual Color rho(const ShadeRec& sr, const Vector3D& wo) const = 0;

protected:
    Sampler* sampler;
    Vector3D normal;
};

#endif //RAYTRACER_BRDF_H
