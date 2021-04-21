#include "PerfectSpecular.h"

#include "Color.h"
#include "Vector3D.h"
#include "ShadeRec.h"


Color PerfectSpecular::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const
{
    return color::black;
}


Color PerfectSpecular::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const
{
    return color::black;
}

Color PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& wo) const
{
    return color::black;
}