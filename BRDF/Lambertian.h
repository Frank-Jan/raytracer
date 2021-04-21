#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "BRDF.h"
#include "Color.h"
#include "constants.h"

class Lambertian : public BRDF
{
public:
    Lambertian(const Color c = color::black, double _kd=0) :
    kd(_kd), cd(c) { }

    Lambertian(double r, double g, double b, double _kd=0) :
    kd(_kd), cd(r,g,b) { }

    Color f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;

    Color sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const;

    Color rho(const ShadeRec& sr, const Vector3D& wo) const;

    double kd;  // diffuse reflection coefficient
    Color cd;   // diffuse color
};

#endif //RAYTRACER_LAMBERTIAN_H
