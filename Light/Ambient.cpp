#include "Ambient.h"
#include "ShadeRec.h"


Ambient::Ambient(const Color &c=Color(1.0), FLOAT ls=1.0) :
color(c), ls(ls)
{ }

Ambient::Ambient(FLOAT r, FLOAT g, FLOAT b, FLOAT ls=1.0) :
color(r,g,b), ls(ls)
{ }

Vector3D Ambient::get_direction(const ShadeRec &sr)
{
    return Vector3D();
}

Color Ambient::L(const ShadeRec &sr)
{
    return ls*color;
}

bool Ambient::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
    return false;
}