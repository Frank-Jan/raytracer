#include "GlossySpecular.h"

#include "BRDF.h"

#include "Color.h"
#include "Vector3D.h"
#include "ShadeRec.h"

GlossySpecular::GlossySpecular() :
cd(1.0), ks(1.0), exp(2.0)
{ }

Color GlossySpecular::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const
{
    double ndotwi = sr.normal*wi;
    Vector3D r = 2 * ndotwi * sr.normal - wi;
    r._normalize(); // just to be sure
    double ndotwo = r * wo;
    if(ndotwo > 0.0)
        return ks * pow(ndotwo, exp);
    return Color();
}


Color GlossySpecular::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const
{
    return color::black;
}

Color GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const
{
    return cd;
}