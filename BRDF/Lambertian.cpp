#include "Lambertian.h"

#include "Color.h"
#include "Vector3D.h"
#include "ShadeRec.h"


Color Lambertian::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const
{
    return kd*cd*M_1_PI;
}


Color Lambertian::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const
{
    // sample wi
    // normalize wi
    // return (kd*cd/(normal*wi))
    return color::black;
}

Color Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const
{
    return kd*cd;
}