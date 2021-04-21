#ifndef RAYTRACER_PERFECTSPECULAR_H
#define RAYTRACER_PERFECTSPECULAR_H

#include "BRDF.h"

class PerfectSpecular : public BRDF
{
public:
    Color f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;

    Color sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const;

    Color rho(const ShadeRec& sr, const Vector3D& wo) const;

    double kr,cr;
};

#endif //RAYTRACER_PERFECTSPECULAR_H
