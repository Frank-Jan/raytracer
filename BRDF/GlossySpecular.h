#ifndef RAYTRACER_GLOSSYSPECULAR_H
#define RAYTRACER_GLOSSYSPECULAR_H

#include "BRDF.h"
#include "Color.h"

class GlossySpecular : public BRDF
{
public:
    GlossySpecular();

    Color f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;

    Color sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const;

    Color rho(const ShadeRec& sr, const Vector3D& wo) const;

    double ks, exp;
    Color cd;
};


#endif //RAYTRACER_GLOSSYSPECULAR_H
